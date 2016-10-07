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
};
												//Initial Board Configuration
int kingPositionCapital,kingPositionSmall;
int globaldepth;
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
//	cout<<listitem;
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
int rating()	{
	return 0;
}
string alphabeta(int depth,int beta,int alpha,string move,int player)	{
//	cout<<"level="<<depth<<endl;
	string listitem=possibleMove();
	if(depth==0 || listitem.length()==0)	{
		return move+to_string((rating()*(player*2-1)));
	}
//	listitem="";
//	cout<<"Number of moves:";
//	int temp;
//	cin>>temp;
//	for(int i=0;i<temp;i++)	{
//		listitem+="1111b";
//	}
	player=1-player;
	for(int i=0;i<listitem.length();i+=5)	{
		makeMove(listitem.substr(i,5));
		flipBoard();
		string returnstring=alphabeta(depth-1,beta,alpha,listitem.substr(i,5),player);
		int value=0;
		for(int j=5;j<returnstring.length();j++)	{
			value=value*10+(returnstring[j]-'0');
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
//	makeMove("7657 ");
//	unmakeMove("7657 ");
	globaldepth=4;
	cout<<possibleMove();
	makeMove(alphabeta(globaldepth,1000000,-1000000,"",0));
//	possibleMove();
	cout<<endl;
	for(int i=0;i<8;i++)	{
		for(int j=0;j<8;j++)	{
			cout<<Board[i][j];
		}
		cout<<endl;
	}
	return 0;
}