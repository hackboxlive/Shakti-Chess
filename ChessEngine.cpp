#include <bits/stdc++.h>
using namespace std;
char Board[][8]={
	{'r','k','b','q','a','b','k','r'},
	{'p','p','p','p','p','p','p','p'},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{'P','P','P','P','P','P','P','P'},
	{'R','K','B','Q','A','B','K','R'},
};								//Initial Board Configuration
int kingPositionCapital,kingPositionSmall;
int globaldepth;
int pawnBoard[][8]={
        { 0,  0,  0,  0,  0,  0,  0,  0},
        {50, 50, 50, 50, 50, 50, 50, 50},
        {10, 10, 20, 30, 30, 20, 10, 10},
        { 5,  5, 10, 25, 25, 10,  5,  5},
        { 0,  0,  0, 20, 20,  0,  0,  0},
        { 5, -5,-10,  0,  0,-10, -5,  5},
        { 5, 10, 10,-20,-20, 10, 10,  5},
        { 0,  0,  0,  0,  0,  0,  0,  0}
	};
int rookBoard[][8]={
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 5, 10, 10, 10, 10, 10, 10,  5},
        {-5,  0,  0,  0,  0,  0,  0, -5},
        {-5,  0,  0,  0,  0,  0,  0, -5},
        {-5,  0,  0,  0,  0,  0,  0, -5},
        {-5,  0,  0,  0,  0,  0,  0, -5},
        {-5,  0,  0,  0,  0,  0,  0, -5},
        { 0,  0,  0,  5,  5,  0,  0,  0}
	};
int knightBoard[][8]={
        {-50,-40,-30,-30,-30,-30,-40,-50},
        {-40,-20,  0,  0,  0,  0,-20,-40},
        {-30,  0, 10, 15, 15, 10,  0,-30},
        {-30,  5, 15, 20, 20, 15,  5,-30},
        {-30,  0, 15, 20, 20, 15,  0,-30},
        {-30,  5, 10, 15, 15, 10,  5,-30},
        {-40,-20,  0,  5,  5,  0,-20,-40},
        {-50,-40,-30,-30,-30,-30,-40,-50}
	};
int bishopBoard[][8]={
        {-20,-10,-10,-10,-10,-10,-10,-20},
        {-10,  0,  0,  0,  0,  0,  0,-10},
        {-10,  0,  5, 10, 10,  5,  0,-10},
        {-10,  5,  5, 10, 10,  5,  5,-10},
        {-10,  0, 10, 10, 10, 10,  0,-10},
        {-10, 10, 10, 10, 10, 10, 10,-10},
        {-10,  5,  0,  0,  0,  0,  5,-10},
        {-20,-10,-10,-10,-10,-10,-10,-20}
    };
int queenBoard[][8]={
        {-20,-10,-10, -5, -5,-10,-10,-20},
        {-10,  0,  0,  0,  0,  0,  0,-10},
        {-10,  0,  5,  5,  5,  5,  0,-10},
        { -5,  0,  5,  5,  5,  5,  0, -5},
        {  0,  0,  5,  5,  5,  5,  0, -5},
        {-10,  5,  5,  5,  5,  5,  0,-10},
        {-10,  0,  5,  0,  0,  0,  0,-10},
        {-20,-10,-10, -5, -5,-10,-10,-20}
    };
int kingMidBoard[][8]={
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-20,-30,-30,-40,-40,-30,-30,-20},
        {-10,-20,-20,-20,-20,-20,-20,-10},
        { 20, 20,  0,  0,  0,  0, 20, 20},
        { 20, 30, 10,  0,  0, 10, 30, 20}
    };
int kingEndBoard[][8]={
        {-50,-40,-30,-20,-20,-30,-40,-50},
        {-30,-20,-10,  0,  0,-10,-20,-30},
        {-30,-10, 20, 30, 30, 20,-10,-30},
        {-30,-10, 30, 40, 40, 30,-10,-30},
        {-30,-10, 30, 40, 40, 30,-10,-30},
        {-30,-10, 20, 30, 30, 20,-10,-30},
        {-30,-30,  0,  0,  0,  0,-30,-30},
        {-50,-30,-30,-30,-30,-30,-30,-50}
};
int score[1001000];
bool kingSafe()	{
	int temp=1;
	int r=kingPositionCapital/8;
	int c=kingPositionCapital%8;
	for(int i=-1;i<=1;i+=2)	{					//For Black Bishop's and Queen's diagonal movement
		for(int j=-1;j<=1;j+=2)	{
			temp=1;
			if((r+temp*i)<0 || (r+temp*i)>7 || (c+temp*j)<0 || (c+temp*j)>7)	{
				continue;
			}
			while(Board[r+temp*i][c+temp*j]==' ')	{
				temp++;
				if((r+temp*i)<0 || (r+temp*i)>7 || (c+temp*j)<0 || (c+temp*j)>7)	{
					break;
				}
			}
			if((r+temp*i)<0 || (r+temp*i)>7 || (c+temp*j)<0 || (c+temp*j)>7)	{
				continue;
			}
			if(Board[r+temp*i][c+temp*j]=='q' || Board[r+temp*i][c+temp*j]=='b')	{
				return false;
			}
		}
	}
	for(int i=-1;i<=1;i++)	{					//For Black Rook's and Queen's straight movement
		int st,en;
		if(i==-1 || i==1)	{
			st=0;
			en=0;
		}
		else	{
			st=-1;
			en=1;
		}
		for(int j=st;j<=en;j+=2)	{
			temp=1;
			if((r+temp*i)<0 || (r+temp*i)>7 || (c+temp*j)<0 || (c+temp*j)>7)	{
				continue;
			}
			while(Board[r+temp*i][c+temp*j]==' ')	{
				temp++;
				if((r+temp*i)<0 || (r+temp*i)>7 || (c+temp*j)<0 || (c+temp*j)>7)	{
					break;
				}
			}
			if((r+temp*i)<0 || (r+temp*i)>7 || (c+temp*j)<0 || (c+temp*j)>7)	{
				continue;
			}
			if(Board[r+temp*i][c+temp*j]=='q' || Board[r+temp*i][c+temp*j]=='r')	{
				return false;
			}
		}
		temp=1;
	}
	int movex[]={-2,-1,1,2,2,1,-1,-2};			//For Black Knight's unique movement
	int movey[]={1,2,2,1,-1,-2,-2,-1};
	for(int i=0;i<8;i++)	{
		if((r+movex[i])<0 || (r+movex[i])>7 || (c+movey[i])<0 || (c+movey[i])>7)	{
			continue;
		}
		if(Board[r+movex[i]][c+movey[i]]=='k')	{
			return false;
		}
	}
	if(!(r-1<0 || r-1>7 || c-1<0 || c-1>7))	{	//For Black Pawn's one step diagonal capture
		if(Board[r-1][c-1]=='p')	{
			return false;
		}
	}
	if(!(r-1<0 || r-1>7 || c+1<0 || c+1>7))	{
		if(Board[r-1][c+1]=='p')	{
			return false;
		}
	}
	for(int i=0;i<9;i++)	{					//For Black King's one step movement
		if(i!=4)	{
			if((r-1+i/3)<0 || (r-1+i/3)>7 || (c-1+i%3)<0 || (c-1+i%3)>7)	{
				continue;
			}
			if(Board[r-1+i/3][c-1+i%3]=='a')	{
				return false;
			}
		}
	}
	return true;
}
string possiblePawn(int pos)	{
	string listitem="";
	char oldPiece;
	int r=pos/8;
	int c=pos%8;
	for(int i=-1;i<=1;i+=2)	{
		if((r-1)<0 || (r-1)>7 || (c+i)<0 || (c+i)>7)	{
			continue;
		}
		if(Board[r-1][c+i]>=98 && Board[r-1][c+i]<=122 && pos>=16)	{
			oldPiece=Board[r-1][c+i];
			Board[r][c]=' ';
			Board[r-1][c+i]='P';
			if(kingSafe())	{
				listitem=listitem+to_string(r)+to_string(c)+to_string(r-1)+to_string(c+i)+oldPiece;
			}
			Board[r][c]='P';
			Board[r-1][c+i]=oldPiece;
		}
		if(Board[r-1][c+i]>=98 && Board[r-1][c+i]<=122 && pos<16)	{
			char temp[]={'Q','R','B','K'};
			for(int j=0;j<4;j++)	{
				oldPiece=Board[r-1][c+i];
				Board[r][c]=' ';
				Board[r-1][c+i]=temp[j];
				if(kingSafe())	{
					listitem=listitem+to_string(c)+to_string(c+i)+oldPiece+temp[j]+'P';
				}
				Board[r][c]='P';
				Board[r-1][c+i]=oldPiece;
			}
		}
	}
	if((!((r-1)<0 || (r-1)>7 || c<0 || c>7)) && Board[r-1][c]==32 && pos>=16)	{
		oldPiece=Board[r-1][c];
		Board[r][c]=' ';
		Board[r-1][c]='P';
		if(kingSafe())	{
			listitem=listitem+to_string(r)+to_string(c)+to_string(r-1)+to_string(c)+oldPiece;
		}
		Board[r][c]='P';
		Board[r-1][c]=oldPiece;
	}
	if((!((r-1)<0 || (r-1)>7 || c<0 || c>7)) && Board[r-1][c]==32 && pos<16)	{
		char temp[]={'Q','R','B','K'};
		for(int j=0;j<4;j++)	{
			oldPiece=Board[r-1][c];
			Board[r][c]=' ';
			Board[r-1][c]=temp[j];
			if(kingSafe())	{
				listitem=listitem+to_string(c)+to_string(c)+oldPiece+temp[j]+'P';
			}
			Board[r][c]='P';
			Board[r-1][c]=oldPiece;
		}
	}
	if((!((r-2)<0 || (r-2)>7 || c<0 || c>7)) && Board[r-1][c]==32 && Board[r-2][c]==32 && r==6)	{
		oldPiece=Board[r-2][c];
		Board[r][c]=' ';
		Board[r-2][c]='P';
		if(kingSafe())	{
			listitem=listitem+to_string(r)+to_string(c)+to_string(r-2)+to_string(c)+oldPiece;
		}
		Board[r][c]='P';
		Board[r-2][c]=oldPiece;
	}
	return listitem;
}
string possibleRook(int pos)	{
	string listitem="";
	char oldPiece;
	int r=pos/8;
	int c=pos%8;
	int temp=1;
	for(int i=-1;i<=1;i++)	{
		int st,en;
		if(i==-1 || i==1)	{
			st=0;
			en=0;
		}
		else	{
			st=-1;
			en=1;
		}
		for(int j=st;j<=en;j+=2)	{
			if((r+temp*i)<0 || (r+temp*i)>7 || (c+temp*j)<0 || (c+temp*j)>7)	{
				continue;
			}
			while(Board[r+temp*i][c+temp*j]==' ')	{
				oldPiece=Board[r+temp*i][c+temp*j];
				Board[r][c]=' ';
				Board[r+temp*i][c+temp*j]='R';
				if(kingSafe())	{
					listitem=listitem+to_string(r)+to_string(c)+to_string(r+temp*i)+to_string(c+temp*j)+oldPiece;
				}
				Board[r][c]='R';
				Board[r+temp*i][c+temp*j]=oldPiece;
				temp++;
				if((r+temp*i)<0 || (r+temp*i)>7 || (c+temp*j)<0 || (c+temp*j)>7)	{
					break;
				}
			}
			if((r+temp*i)<0 || (r+temp*i)>7 || (c+temp*j)<0 || (c+temp*j)>7)	{
				continue;
			}
			if(Board[r+temp*i][c+temp*j]>=97 && Board[r+temp*i][c+temp*j]<=122)	{
				oldPiece=Board[r+temp*i][c+temp*j];
				Board[r][c]=' ';
				Board[r+temp*i][c+temp*j]='R';
				if(kingSafe())	{
					listitem=listitem+to_string(r)+to_string(c)+to_string(r+temp*i)+to_string(c+temp*j)+oldPiece;
				}
				Board[r][c]='R';
				Board[r+temp*i][c+temp*j]=oldPiece;
			}
			temp=1;
		}
	}
	return listitem;
}
string possibleKnight(int pos)	{
	string listitem="";
	char oldPiece;
	int r=pos/8;
	int c=pos%8;
	int movex[]={-2,-1,1,2,2,1,-1,-2};
	int movey[]={1,2,2,1,-1,-2,-2,-1};
	for(int i=0;i<8;i++)	{
		if((r+movex[i])<0 || (r+movex[i])>7 || (c+movey[i])<0 || (c+movey[i])>7)	{
			continue;
		}
		if(Board[r+movex[i]][c+movey[i]]==32 || (Board[r+movex[i]][c+movey[i]]>=97 && Board[r+movex[i]][c+movey[i]]<=122))	{
			oldPiece=Board[r+movex[i]][c+movey[i]];
			Board[r][c]=' ';
			Board[r+movex[i]][c+movey[i]]='K';
			if(kingSafe())	{
				listitem=listitem+to_string(r)+to_string(c)+to_string(r+movex[i])+to_string(c+movey[i])+oldPiece;
			}
			Board[r][c]='K';
			Board[r+movex[i]][c+movey[i]]=oldPiece;
		}
	}
	return listitem;
}
string possibleBishop(int pos)	{
	string listitem="";
	char oldPiece;
	int r=pos/8;
	int c=pos%8;
	int temp=1;
	for(int i=-1;i<=1;i+=2)	{
		for(int j=-1;j<=1;j+=2)	{
			if((r+temp*i)<0 || (r+temp*i)>7 || (c+temp*j)<0 || (c+temp*j)>7)	{
				continue;
			}
			while(Board[r+temp*i][c+temp*j]==' ')	{
				oldPiece=Board[r+temp*i][c+temp*j];
				Board[r][c]=' ';
				Board[r+temp*i][c+temp*j]='B';
				if(kingSafe())	{
					listitem=listitem+to_string(r)+to_string(c)+to_string(r+temp*i)+to_string(c+temp*j)+oldPiece;
				}
				Board[r][c]='B';
				Board[r+temp*i][c+temp*j]=oldPiece;
				temp++;
				if((r+temp*i)<0 || (r+temp*i)>7 || (c+temp*j)<0 || (c+temp*j)>7)	{
					break;
				}
			}
			if((r+temp*i)<0 || (r+temp*i)>7 || (c+temp*j)<0 || (c+temp*j)>7)	{
				continue;
			}
			if(Board[r+temp*i][c+temp*j]>=97 && Board[r+temp*i][c+temp*j]<=122)	{
				oldPiece=Board[r+temp*i][c+temp*j];
				Board[r][c]=' ';
				Board[r+temp*i][c+temp*j]='B';
				if(kingSafe())	{
					listitem=listitem+to_string(r)+to_string(c)+to_string(r+temp*i)+to_string(c+temp*j)+oldPiece;
				}
				Board[r][c]='B';
				Board[r+temp*i][c+temp*j]=oldPiece;
			}
			temp=1;
		}
	}
	return listitem;
}
string possibleQueen(int pos)	{
	string listitem="";
	char oldPiece;
	int r=pos/8;
	int c=pos%8;
	int temp=1;
	for(int i=-1;i<=1;i++)	{
		for(int j=-1;j<=1;j++)	{
			if(j==0 && i==0)	{
				continue;
			}
			if((r+temp*i)<0 || (r+temp*i)>7 || (c+temp*j)<0 || (c+temp*j)>7)	{
				continue;
			}
			while(Board[r+temp*i][c+temp*j]==' ')	{
				oldPiece=Board[r+temp*i][c+temp*j];
				Board[r][c]=' ';
				Board[r+temp*i][c+temp*j]='Q';
				if(kingSafe())	{
					listitem=listitem+to_string(r)+to_string(c)+to_string(r+temp*i)+to_string(c+temp*j)+oldPiece;
				}
				Board[r][c]='Q';
				Board[r+temp*i][c+temp*j]=oldPiece;
				temp++;
				if((r+temp*i)<0 || (r+temp*i)>7 || (c+temp*j)<0 || (c+temp*j)>7)	{
					break;
				}
			}
			if((r+temp*i)<0 || (r+temp*i)>7 || (c+temp*j)<0 || (c+temp*j)>7)	{
				continue;
			}
			if(Board[r+temp*i][c+temp*j]>=97 && Board[r+temp*i][c+temp*j]<=122)	{
				oldPiece=Board[r+temp*i][c+temp*j];
				Board[r][c]=' ';
				Board[r+temp*i][c+temp*j]='Q';
				if(kingSafe())	{
					listitem=listitem+to_string(r)+to_string(c)+to_string(r+temp*i)+to_string(c+temp*j)+oldPiece;
				}
				Board[r][c]='Q';
				Board[r+temp*i][c+temp*j]=oldPiece;
			}
			temp=1;
		}
	}
	return listitem;
}
string possibleKing(int pos)	{
	string listitem="";
	char oldPiece;
	int r=pos/8;
	int c=pos%8;
	for(int i=0;i<9;i++)	{
		if(i!=4)	{
			if((r-1+i/3)<0 || (r-1+i/3)>7 || (c-1+i%3)<0 || (c-1+i%3)>7)	{
				continue;
			}
			if((Board[r-1+i/3][c-1+i%3]<=122 && Board[r-1+i/3][c-1+i%3]>=97) || (Board[r-1+i/3][c-1+i%3]==32))	{
				oldPiece=Board[r-1+i/3][c-1+i%3];
				Board[r][c]=' ';
				Board[r-1+i/3][c-1+i%3]='A';
				int kingTemp=kingPositionCapital;
				kingPositionCapital=pos+(i/3)*8+i%3-9;
				if(kingSafe())	{
					listitem=listitem+to_string(r)+to_string(c)+to_string(r-1+i/3)+to_string(c-1+i%3)+oldPiece;
				}
				Board[r][c]='A';
				Board[r-1+i/3][c-1+i%3]=oldPiece;
				kingPositionCapital=kingTemp;
			}
		}
	}
	return listitem;
}
string possibleMove()	{
	string listitem="";
	for(int i=0;i<64;i++)	{
		switch(Board[i/8][i%8])	{
			case 'P':
				listitem+=possiblePawn(i);
				break;
			case 'R':
				listitem+=possibleRook(i);
				break;
			case 'K':
				listitem+=possibleKnight(i);
				break;
			case 'B':
				listitem+=possibleBishop(i);
				break;
			case 'Q':
				listitem+=possibleQueen(i);
				break;
			case 'A':
				listitem+=possibleKing(i);
				break;
		}
	}
	return listitem;
}
void makeMove(string listitem)	{
	if(listitem[4]!='P')	{
		Board[listitem[2]-48][listitem[3]-48]=Board[listitem[0]-48][listitem[1]-48];
		Board[listitem[0]-48][listitem[1]-48]=' ';
		if(Board[listitem[2]-48][listitem[3]-48]=='A')	{
			kingPositionCapital=8*(listitem[2]-48)+(listitem[3]-48);
		}
	}
	else	{
		Board[0][listitem[1]-48]=listitem[3];
		Board[1][listitem[0]-48]=' ';
	}
}
void unmakeMove(string listitem)	{
	if(listitem[4]!='P')	{
		Board[listitem[0]-48][listitem[1]-48]=Board[listitem[2]-48][listitem[3]-48];
		Board[listitem[2]-48][listitem[3]-48]=listitem[4];
		if(Board[listitem[0]-48][listitem[1]-48]=='A')	{
			kingPositionCapital=8*(listitem[0]-48)+(listitem[1]-48);
		}

	}
	else	{
		Board[0][listitem[1]-48]=listitem[2];
		Board[1][listitem[0]-48]='P';
	}
}
void flipBoard()	{
	for(int i=0;i<4;i++)	{
		for(int j=0;j<8;j++)	{
			char ch=Board[i][j];
			Board[i][j]=Board[7-i][7-j];
			Board[7-i][7-j]=ch;
		}
	}
	for(int i=0;i<8;i++)	{
		for(int j=0;j<8;j++)	{
			if(Board[i][j]>='A' && Board[i][j]<='Z')	{
				Board[i][j]=Board[i][j]+32;
			}
			else if(Board[i][j]>='a' && Board[i][j]<='z')	{
				Board[i][j]=Board[i][j]-32;
			}
		}
	}
	int temp=kingPositionCapital;
	kingPositionCapital=63-kingPositionSmall;
	kingPositionSmall=63-temp;
	return;
}
int rateAttack()	{
	int counter=0;
	int temppos=kingPositionCapital;
	for(int i=0;i<64;i++)	{
		if(Board[i/8][i%8]=='P')	{
			kingPositionCapital=i;
			if(!kingSafe())	{
				counter-=64;
			}
		}
		if(Board[i/8][i%8]=='R')	{
			kingPositionCapital=i;
			if(!kingSafe())	{
				counter-=500;
			}
		}
		if(Board[i/8][i%8]=='K')	{
			kingPositionCapital=i;
			if(!kingSafe())	{
				counter-=300;
			}
		}
		if(Board[i/8][i%8]=='B')	{
			kingPositionCapital=i;
			if(!kingSafe())	{
				counter-=300;
			}
		}
		if(Board[i/8][i%8]=='Q')	{
			kingPositionCapital=i;
			if(!kingSafe())	{
				counter-=900;
			}
		}
	}
	kingPositionCapital=temppos;
	if(!kingSafe())	{
		counter-=200;
	}
	return counter/2;
}
int rateMaterial()	{
	int counter=0;
	int BishopCounter=0;
	for(int i=0;i<64;i++)	{
		if(Board[i/8][i%8]=='P')	{
			counter+=100;
		}
		if(Board[i/8][i%8]=='R')	{
			counter+=500;
		}
		if(Board[i/8][i%8]=='K')	{
			counter+=300;
		}
		if(Board[i/8][i%8]=='B')	{
			BishopCounter++;
		}
		if(Board[i/8][i%8]=='Q')	{
			counter+=900;
		}
	}
	if(BishopCounter>=2)	{
		counter+=300*BishopCounter;
	}
	else	{
		if(BishopCounter==1)	{
			counter+=250;
		}
	}
	return counter;
}
int rateMovability(int listlength,int depth,int material)	{
	int counter=listlength;
	if(listlength==0)	{
		if(!kingSafe())	{
			counter+=depth*(-200000);
		}
		else	{
			counter+=depth*(-150000);
		}
	}
	return counter;
}
int ratePositional(int material)	{
	int counter=0;
	for(int i=0;i<64;i++)	{
		if(Board[i/8][i%8]=='P')	{
			counter+=pawnBoard[i/8][i%8];
		}
		if(Board[i/8][i%8]=='R')	{
			counter+=rookBoard[i/8][i%8];
		}
		if(Board[i/8][i%8]=='K')	{
			counter+=knightBoard[i/8][i%8];
		}
		if(Board[i/8][i%8]=='B')	{
			counter+=bishopBoard[i/8][i%8];
		}
		if(Board[i/8][i%8]=='Q')	{
			counter+=queenBoard[i/8][i%8];
		}
		if(Board[i/8][i%8]=='A')	{
			if(material>=1750)	{
				counter+=kingMidBoard[i/8][i%8];
				counter+=possibleKing(kingPositionCapital).length()*10;
			}
			else	{
				counter+=kingEndBoard[i/8][i%8];
				counter+=possibleKing(kingPositionCapital).length()*30;
			}
		}
	}
	return counter;
}
int rating(int listlength,int depth)	{
	int counter=0;
	int material=rateMaterial();
	counter+=rateAttack();
	counter+=material;
	counter+=rateMovability(listlength,depth,material);
	counter+=ratePositional(material);
	flipBoard();
	material=rateMaterial();
	counter-=rateAttack();
	counter-=material;
	counter-=rateMovability(listlength,depth,material);
	counter-=ratePositional(material);
	flipBoard();
	return -(counter+50*depth);
}
string sortMoves(string listitem)	{
	for(int i=0;i<listitem.length();i+=5)	{
		makeMove(listitem.substr(i,5));
		score[i/5]=(-1)*rating(-1,0);
		unmakeMove(listitem.substr(i,5));
	}
	string newListA="",newListB=listitem;
	int iter;
	if(6<listitem.length()/5)	{
		iter=6;
	}
	else	{
		iter=listitem.length()/5;
	}
	for(int i=0;i<iter;i++)	{
		int maxx=-1000000,maxl=0;
		for(int j=0;j<listitem.length()/5;j++)	{
			if(score[j]>maxx)	{
				maxx=score[j];
				maxl=j;
			}
		}
		score[maxl]=-1000000;
		string strs=listitem.substr(maxl*5,5);
		newListA+=strs;
		int xpos;
		for(int j=0;j<newListB.length();j+=5)	{
			if(newListB.substr(j,5).compare(strs)==0)	{
				xpos=j;
			}
		}
		newListB.erase(xpos,5);
	}
	return newListA+newListB;
}
string alphabeta(int depth,int beta,int alpha,string move,int player)	{
	string listitem=possibleMove();
	if(depth==0 || listitem.length()==0)	{
		return move+to_string((rating(listitem.length(),depth)*(player*2-1)));
	}
	listitem=sortMoves(listitem);
	player=1-player;
	for(int i=0;i<listitem.length();i+=5)	{
		makeMove(listitem.substr(i,5));
		flipBoard();
		string returnstring=alphabeta(depth-1,beta,alpha,listitem.substr(i,5),player);
		int value=0;
		int fff=0;
		for(int j=5;j<returnstring.length();j++)	{
			if(returnstring[j]>='0' && returnstring[j]<='9')	{
				value=value*10+(returnstring[j]-'0');
			}
		}
		if(returnstring[5]=='-')	{
			value=value*-1;
		}
		flipBoard();
		unmakeMove(listitem.substr(i,5));
		if(player==0)	{
			if(value<=beta)	{
				beta=value;
				if(depth==globaldepth)	{
					move=returnstring.substr(0,5);
				}
			}
		}
		else	{
			if(value>alpha)	{
				alpha=value;
				if(depth==globaldepth)	{
					move=returnstring.substr(0,5);
				}
			}
		}
		if(alpha>=beta)	{
			if(player==0)	{
				return move+to_string(beta);
			}
			else	{
				return move+to_string(alpha);
			}
		}
	}
	if(player==0)	{
		return move+to_string(beta);
	}
	else	{
		return move+to_string(alpha);
	}
}
int main()	{
	for(int i=0;i<64;i++)	{
		if(Board[i/8][i%8]=='A')	{
			kingPositionCapital=i;
		}
		if(Board[i/8][i%8]=='a')	{
			kingPositionSmall=i;
		}
	}
	string str;
	while(1)	{
		globaldepth=4;
		cout<<possibleMove()<<endl;
		cin>>str;
		if(str.length()==4)	{
			str=str+" ";
		}
		makeMove(str);
		string strs=alphabeta(globaldepth,1000000,-1000000,"",0);
		cout<<strs<<endl;
		makeMove(strs);
		for(int i=0;i<8;i++)	{
			for(int j=0;j<8;j++)	{
				cout<<Board[i][j];
			}
			cout<<endl;
		}
	}
	return 0;
}