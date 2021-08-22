#include "qdicethread.h"

#include <QDebug>
#include <QRandomGenerator>

void QDiceThread::run() {
  m_stop = false;
  m_seq = 0;
  QRandomGenerator geneRand;
  // qsrand(QTime::currentTime().msec());
  while (!m_stop) {
    if (!m_paused) {
      m_diceValue = geneRand.generate();
      m_diceValue = (m_diceValue % 6) + 1;
      m_seq++;
      emit newValue(m_seq, m_diceValue);
    }
    msleep(500);
  }
  quit();
}

QDiceThread::QDiceThread() {}

void QDiceThread::diceBegin() { m_paused = false; }

void QDiceThread::dicePause() { m_paused = true; }

void QDiceThread::stopThread() { m_stop = true; }
