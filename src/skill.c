//==============================================//
//								       			//
//					 Skill                		//
//                                     			//
//----------------------------------------------//
// File : skill.c */                 			//
//----------------------------------------------//
// Implementasi ADT Skill                          	//
// Skill memiliki jenis dan efek yang beragam	//
// pada keberjalanan game                       //
//==============================================//

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include"skill.h"

///////////////////////////
// 		CONSTRUCTOR 	 //
///////////////////////////
Skill SkillCreate(int kind){
/* Mengembalikan skill yang kindnya telah diset */
	Skill S;
	SkillKind(S)=kind;
	return S;
}

//////////////////////////////////
// 		 SKILL OPERATIONS		//
//////////////////////////////////
char* SkillGetName(int kind){
/* Mengembalikan string nama skill dengan kind tertentu */
	if (kind==1){
		return "Instant Upgrade";
	}else if (kind==2){
		return "Extra Turn";
	}else if (kind==3){
		return "Instant Reinforcement";
	}else if (kind==4){
		return "Barrage";
	}
}

char* SkillGetAcronym(int kind){
/* Mengembalikan akronim nama skill dengan kind tertentu */
	if (kind==1){
		return "IU";
	}else if (kind==2){
		return "ET";
	}else if (kind==3){
		return "IR";
	}else if (kind==4){
		return "BR";
	}
}


char* SkillGetEffect(int kind){
/* Mengembalikan string efek skill dengan kind tertentu */
	if (kind==1){
		return "Instant Upgrade (IU)\nEfek :	Seluruh bangunan yang dimiliki pemain akan naik 1 level.\n	Pemain tidak akan mendapat skill ini selain dari daftar skill awal.\n";
	}else if (kind==2){
		return "Extra Turn (ET)\nEfek :	Setelah giliran pengaktifan skill ini berakhir, pemain selanjutnya tetap pemainyang sama.\n";
	}else if (kind==3){
		return "Instant Reinforcement (IR)\nEfek :	Seluruh bangunan mendapatkan tambahan 5 pasukan.\n	Pemain mendapat skill ini di akhir gilirannya bila semua bangunan yang ia \n	miliki memiliki level 4\n";
	}else if (kind==4){
		return "Barrage (BR)\nEfek :	Jumlah pasukan pada seluruh bangunan musuh akan berkurang sebanyak 10 pasukan.\n	Pemain mendapat skill ini jika lawan baru saja bertambah bangunannya menjadi 10 bangunan.\n";
	}
}


// Gonna still be added