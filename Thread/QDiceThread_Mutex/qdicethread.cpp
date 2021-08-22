#include "qdicethread.h"

#include <QDebug>
#include <QMutexLocker>
#include <QRandomGenerator>

void QDiceThread::run() {
  m_stop = false;
  m_seq = 0;
  QRandomGenerator geneRand;
  while (!m_stop) {
    if (!m_paused) {
#if 0
      mutex.lock();
      m_diceValue = geneRand.generate();
      m_diceValue = (m_diceValue % 6) + 1;
      m_seq++;
      mutex.unlock();
#else
      // Locker对象利用栈对象自动析构提醒完成unlock操作
      QMutexLocker Locker(&mutex);
      m_diceValue = geneRand.generate();
      m_diceValue = (m_diceValue % 6) + 1;
      m_seq++;
#endif
    }
    msleep(500);
  }
  quit();
}

QDiceThread::QDiceThread() {}

void QDiceThread::diceBegin() { m_paused = false; }

void QDiceThread::dicePause() { m_paused = true; }

void QDiceThread::stopThread() { m_stop = true; }

bool QDiceThread::readValue(int *seq, int *diceValue) {
  if (mutex.tryLock()) {
    *seq = m_seq;
    *diceValue = m_diceValue;
    mutex.unlock();
    return true;
  } else
    return false;
}
