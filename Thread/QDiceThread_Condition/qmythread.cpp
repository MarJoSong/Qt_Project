#include "qmythread.h"

#include <QDebug>
#include <QMutexLocker>
#include <QRandomGenerator>

QMutex mutex;
QWaitCondition dataAvailable;
int seq = 0;
uint diceValue;

void QThreadProducer::run() {
  m_stop = false;
  seq = 0;
  QRandomGenerator geneRand;
  while (!m_stop) {
    mutex.lock();
    diceValue = geneRand.generate();
    diceValue = (diceValue % 6) + 1;
    seq++;
    mutex.unlock();
    dataAvailable.wakeAll();
    msleep(500);
  }
}

void QThreadProducer::stopThread() {
  QMutexLocker locker(&mutex);
  m_stop = true;
}

void QThreadConsumer::run() {
  m_stop = false;
  while (!m_stop) {
    mutex.lock();
    dataAvailable.wait(&mutex);
    qDebug() << seq << " " << diceValue;
    emit newValue(seq, diceValue);
    mutex.unlock();
  }
}

void QThreadConsumer::stopThread() {
  QMutexLocker locker(&mutex);
  m_stop = true;
}
