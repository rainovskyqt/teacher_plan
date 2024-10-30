#ifndef TYPES_H
#define TYPES_H

enum class WorkType{
    Educational = 1,
    MethodicWork,
    ResearchingWork,
    SportWork,
    OtherWork,
    Total
};

enum class PlanStatus{
    NotSet,
    Development,
    PendingApproval,
    Approved
};

Q_DECLARE_METATYPE(WorkType)
Q_DECLARE_METATYPE(PlanStatus)

#endif // TYPES_H
