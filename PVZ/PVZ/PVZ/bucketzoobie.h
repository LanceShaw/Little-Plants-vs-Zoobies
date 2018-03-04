#ifndef BUCKETZOOBIE_H
#define BUCKETZOOBIE_H

#include "zoobie.h"
#include "QLabel"

class BucketZoobie: public Zoobie
{
    Q_OBJECT
public:
    explicit BucketZoobie(QWidget* parent=0);
};

#endif // BUCKETZOOBIE_H
