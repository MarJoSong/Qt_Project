#ifndef QDICETHREAD_H
#define QDICETHREAD_H

#include <QMutex>
#include <QObject>
#include <QThread>

#include "stdafx.h"

class QDiceThread : public QThread {
  Q_OBJECT
 private:
  QMutex mutex;
  int m_seq = 0;
  uint m_diceValue;
  bool m_paused = true;
  bool m_stop = false;

 protected:
  void run() Q_DECL_OVERRIDE;

 public:
  QDiceThread();
  void diceBegin();
  void dicePause();
  void stopThread();
  bool readValue(int* seq, int* diceValue);

 signals:
  void newValue(int seq, int diceValue);
};

#endif  // QDICETHREAD_H
