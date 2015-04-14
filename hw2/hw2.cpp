#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "click.h"

using namespace std;

int i,j,k,x,d,total_user;
vector<User> tmp(1000000);

bool compareadid( const User &user1, const User &user2)
{
	int i;
	if(user1.adid != user2.adid)
		return user1.adid < user2.adid;
	else if(user1.url != user2.url)
		return user1.url < user2.url;
	else if(user1.ad[0] != user2.ad[0])
		return user1.ad[0] < user2.ad[0];	
	else if(user1.ad[1] != user2.ad[1])
                return user1.ad[1] < user2.ad[1];
	else if(user1.ad[2] != user2.ad[2])
                return user1.ad[2] < user2.ad[2];
	else if(user1.ad[3] != user2.ad[3])
                return user1.ad[3] < user2.ad[3];
	else return 0;
}

bool compareid( const User &user1, const User &user2)
{
	return user1.id < user2.id;
}

void display( vector<User> user)
{
	for(i = 0; i < user.size(); i++)
        {

                printf("Data for user id %d :",user[i].id);
                printf("%d %d %d %llu %d %d %d ",user[i].click,user[i].impression,user[i].adid,user[i].url,user[i].depth,user[i].position, user[i].query);
                for(k = 0; k < 4; k++)
                        cout << user[i].ad[k] << " ";
                cout << endl;
        }

}

void get( vector<User> user, int id, int adid, int q, int p, int d)
{
	//cout << "enter get\n" ; 
        int total_click = 0;
        int total_impressed = 0;
        int total_user = 0;     
        i = 0;
        while(user[i].id != id && i < user.size())
        {
                i++;
        }
        while(user[i].id == id && i < user.size())
        {
		if(user[i].adid == adid && user[i].query == q && user[i].position == p && user[i].depth == d)
                {
                        total_click += user[i].click;
                        total_impressed += user[i].impression;
                }
                i++;
        }
        cout << "********************" << endl;
        cout << total_click << " " << total_impressed << endl;
        cout << "********************" << endl ;
}

void clicked( vector<User> user, int id)
{
        i = 0;
        while(user[i].id != id && i < user.size())
        {
                i++;
        }
	cout << "********************" << endl;
        while(user[i].id == id && i < user.size())
        {
		if(user[i].click > 0)
                   cout << user[i].adid << " " << user[i].query << endl;
		i++;
        }
	cout << "********************" << endl;
}

void impressed(vector<User> user, int id1, int id2)
{
        i = 0;
	//search id1 and id2 and then copy them to new vector
	int starts,size;
        while(user[i].id != id1 && i < user.size())
        {
                i++;
        }
        starts = i;
        while(user[i].id == id1 && i < user.size())
        {
                i++;
        }
	size = i-starts;
	tmp.resize(size);
        copy(user.begin()+starts,user.begin()+i,tmp.begin());
	
        i = 0;
        while(user[i].id != id2 && i < user.size())
        {
                i++;
        }
        starts = i;
        while(user[i].id == id2 && i < user.size())
        {
                i++;
        }
	size += (i-starts);
	tmp.resize(size);
	copy(user.begin()+starts,user.begin()+i,tmp.begin()+size-i+starts);
	//display(user);
	//cout << start1 << " " << end1 << " " << start2 << " " << end2 << "id1 = " << id1 << " id2 = " << id2 << endl;

	//sort by increasing adid
        sort(tmp.begin(),tmp.end(),compareadid);
	//display(tmp);	
	//erase nonrepeated adid
	i = 0;
	while(i < tmp.size() || j < tmp.size())
	{
		j = i+1;
		while(tmp[i].adid == tmp[j].adid && j < tmp.size())
                        j++;
		if(i == (j-1))
                {
			//cout << "before : " << tmp.size() << endl;
                        tmp.erase(tmp.begin()+i);
			i = j-1;
			//cout << "after : " << tmp.size() << endl;
			//display(tmp);
                }
                else
                {
			//cout << "before erase " << tmp.size() << endl;
			//cout << "i = " << i << " j = " << j << endl;
			//if repeated erase repeated property ad or impression 0
			for(x = i; x < j; x++)
			{
				for(k = x+1; k < j; k++)
				{
					//cout << "x = " << x << " k = " << k << " j = " << j << endl;
					if((tmp[x].url == tmp[k].url && tmp[x].ad[0] == tmp[k].ad[0] && tmp[x].ad[1] == tmp[k].ad[1] && tmp[x].ad[2] == tmp[k].ad[2] && tmp[x].ad[3] == tmp[k].ad[3]) || tmp[k].impression == 0)
		                        {
	                	                tmp.erase(tmp.begin()+x);
						k--;        	                        
		                                j--;
						x--;
		                        }				
				}
			}
                        i = j;
                        j++;
			//cout << "after erase : " << tmp.size() << endl;
                }
	}
	//cout << tmp.size() << endl;
	//display(tmp);

	cout << "********************" << endl;	

	i = 0;
	cout << tmp[i].adid << endl << "\t" << tmp[i].url << " " << tmp[i].ad[0] << " " << tmp[i].ad[1] << " " << tmp[i].ad[2] << " " << tmp[i].ad[3] << endl;
	
	for(i = 1; i < tmp.size(); i++)
		if(tmp[i].adid == tmp[i-1].adid)
	cout << "	" << tmp[i].url << " " << tmp[i].ad[0] << " " << tmp[i].ad[1] << " " << tmp[i].ad[2] << " " << tmp[i].ad[3] << endl;
	else 
		cout << tmp[i].adid << endl << "\t" << tmp[i].url << " " << tmp[i].ad[0] 
		     << " " << tmp[i].ad[1] << " " << tmp[i].ad[2] << " " << tmp[i].ad[3] << endl;

	cout << "********************" << endl;
	tmp.clear();
}


void profit( vector<User> user, int adid, double num)
{
	sort(user.begin(), user.end(), compareadid);
	 i = 0;
        while(user[i].adid != adid && i < user.size())
        {
                i++;
        }
        int start = i;
        while(user[i].adid == adid && i < user.size())
        {
                i++;
        }
	//resize vector tmp
        tmp.resize(i-start);
	//insert the data with adid = adid to tmp
	//cout << i-start << endl;
	copy(user.begin()+start,user.begin()+i,tmp.begin());
	//display(tmp);
	
	//sort by id
	sort(tmp.begin(),tmp.end(),compareid);

	cout << "********************" << endl;
	i = 0;
	j = i+1;
	double total,total_click,total_impressed;
	x = 0;
	while(i < tmp.size() || j < tmp.size())
	{
		while(tmp[i].id == tmp[j].id && j < tmp.size())
			j++;
		total_click = 0;
		total_impressed = 0;
		for(k = i; k < j; k++)
		{
			total_click +=tmp[k].click;
			total_impressed += tmp[k].impression;
		}
		total = total_click/total_impressed;
		//cout << total << endl;
		if(total >= num)
			cout << tmp[i].id << endl;
		i = j;
		j++;
	}
	cout << "********************" << endl;
}

bool compare( const User &user1, const User &user2)
{
	if(user1.id != user2.id)
		return user1.id < user2.id;
	else if(user1.adid != user2.adid)
		return user1.adid < user2.adid;
	else return user1.query < user2.query;
}

int main(int argc, char* argv[])
{
	//printf("program start\n");
	unsigned long long int temp[12];	
	FILE *fp;
	
	vector<User> user;
	User users;
	//printf("program continue\n");
	//ostream_iterator<long long int> VecOut(cout, " ");
	//cout << "vector size : " << user.size() << " max size : " << user.max_size() << endl;
	//int count[max];
	char command[10000];
	
	//open file
	fp = fopen(argv[1],"r");
	
	i = 0;
	while(fgets(command,1000,fp) != NULL)
	{
		//cout << "temp = " << temp[i] << " i = " << i <<endl;
		sscanf(command,"%d %d %llu %d %d %d %d %d %d %d %d %d",&users.click,&users.impression,&users.url,&users.adid,&users.ad[0],&users.depth,&users.position,&users.query,&users.ad[1],&users.ad[2],&users.ad[3],&users.id);
		user.push_back(users);
		/*if(i == 11)
		{
			user[j].click 		= temp[0];
			user[j].impression	= temp[1];
			user[j].url		= temp[2];
			//printf("c = %lld\n",user[j].url);
			//cout << user[j].url << endl;
			user[j].adid		= temp[3];
			user[j].ad[0]		= temp[4];
			user[j].depth		= temp[5];
			user[j].position	= temp[6];
			user[j].query		= temp[7];
			for(k = 8; k < 11; k++)
				user[j].ad[k-7] = temp[k];
			user[j].id = temp[11];
			//cout << "insert success" << endl;
			i = 0;
			j++;
		}
		else 
		{
			i++;
		}*/
		i++;
	}
	fclose(fp);
	//cout << "get data success\n" ;
	//total_user = i;
	//user.resize(total_user);
	sort(user.begin(),user.end(),compare);
	//cout << "sort done\n" ;
	//display(user);
	char tmp[100];
	int id1,id2,adid,q,p,d;
	double num;

	while(gets(command))
	{
		//cout << command[0] << endl;
		if((strstr(command,"get")) != NULL)
		{
			sscanf(command,"%s %d %d %d %d %d",tmp,&id1,&adid,&q,&p,&d);
			get(user,id1,adid,q,p,d);
		}
		else if((strstr(command,"clicked")) != NULL)
		{
			sscanf(command,"%s %d",tmp,&id1);
			clicked(user,id1);
		}
		else if((strstr(command,"impressed")) != NULL)
		{
			sscanf(command,"%s %d %d",tmp,&id1,&id2);
			impressed(user,id1,id2);
		}
		else if((strstr(command,"profit")) != NULL)
		{
			sscanf(command,"%s %d %lf",tmp,&id1,&num);
			profit(user,id1,num);
		}	
		else if((strstr(command,"quit")) != NULL)
		{
			break;
		}
	}
	return 0;
}
