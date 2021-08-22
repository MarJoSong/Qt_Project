#ifndef QMYTHREAD_H
#define QMYTHREAD_H

#include <QMutex>
#include <QObject>
#include <QThread>
#include <QWaitCondition>

#include "stdafx.h"

class QThreadProducer : public QThread {
  Q_OBJECT
 private:
  bool m_stop = false;

 protected:
  void run() Q_DECL_OVERRIDE;

 public:
  QThreadProducer(){};
  void stopThread();
  ;
};

class QThreadConsumer : public QThread {
  Q_OBJECT
 private:
  bool m_stop = false;

 protected:
  void run() Q_DECL_OVERRIDE;

 public:
  QThreadConsumer(){};
  void stopThread();
  ;

 signals:
  void newValue(int seq, int diceValue);
};

#endif  // QMYTHREAD_H
