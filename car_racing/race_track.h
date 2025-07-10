#ifndef RACE_TRACK_H
#define RACE_TRACK_H
class racetrack{
public:
    explicit racetrack(int finish=0)
        : finish_(finish){}
    bool ckeckfinish(int position) const{
        if(finish_>position)return false;
        else return true;
    }
    void setfinish(int finishline){
        finish_=finishline;
    }

private:

    int finish_;
};

#endif // RACE_TRACK_H
