
#include "skill.h"
#include "skillqueue.h"

Skill S,Sdel;
SkillQueue Q;
int x;


int main(){
    do{
        scanf("%d",&x);
        S=SkillCreate(x);
        if(x>=0 && x<=4){
            printf("%s",SkillGetName(SkillKind(S)));
            printf("%s",SkillGetAcronym(SkillKind(S)));
            printf("%s",SkillGetEffect(SkillKind(S)));
        }
    }while(x>=0 && x<=4);
    SkillQueueCreateEmpty(&Q);    
    PrintQueueSkill(Q);
    do{
        scanf("%d",&x);
        S=SkillCreate(x);
        if(x>=0 && x<=4 && !IsSkillQueueFull(Q)){
            SkillQueueAddSkill(&Q,S);
        }
        printf("NbElmt = %d\n",SkillQueueNBElmt(Q));
        PrintQueueSkill(Q);
    }while(x>=0 && x<=4);
    do{
        SkillQueueDelSkill(&Q,&Sdel);
        printf("Dihapus %s\n",SkillGetName(SkillKind(Sdel)));
        printf("NbElmt = %d\n",SkillQueueNBElmt(Q));
        PrintQueueSkill(Q);
        printf("\n");
    }while(!IsSkillQueueEmpty(Q));

    printf("Selesai\n");
}