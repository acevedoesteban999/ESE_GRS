#pragma once
#include <iostream>
#include <winsock.h>
#include <windows.h>
#include <string>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
//enum ConnectionType
//{
// CONNECTION,TCP_IP_SERVER,TCP_IP_CLIENT,SERIAL_PORT
//};
//class Connection
//{
//protected:
//	ConnectionType t;
//	WSADATA wsData;
//	SOCKET server;
//	SOCKADDR_IN serveraddr,clientaddr;
//	bool IsConectado;
//	bool error;
//	char*errorstr,*ip,*message,*buffer; 
//	unsigned Port;
//public:
//	mutex m;
//	Connection(){
//		t=ConnectionType::CONNECTION;
//		IsConectado=error=false;
//		errorstr=new char[1];
//		ip=new char[1];
//		message=new char[1];
//		buffer=new char[1024];
//		Port=0;
//	};
//	virtual ~Connection()
//	{
//		delete []errorstr;
//		delete[]ip;
//		delete[]message;
//		delete []buffer;
//	
//	};
//	virtual void CloseConnection(){};
//	virtual bool inicializa(const char*Ip, unsigned long Port){return false;};
//	virtual char* Recibir()
//	{
//		/*if(EstaConectado())
//		{
//			 memset(buffer,0,sizeof(buffer));
//			 int n=recv(t==ConnectionType::TCP_IP_SERVER?cliente:server,buffer,sizeof(buffer),0);
//			 if(n==0)
//			 {
//				 string s("Error 0 ");
//				 errorstr=new char[s.length()+1];
//				 for(unsigned i=0;i<s.length();i++)
//					 errorstr[i]=s[i];
//				 error=true;
//				 return NULL;
//			 }
//			 if(n==-1)
//			 {
//					string s("C_Error 1 ");
//					errorstr=new char[s.length()+1];
//					for(unsigned i=0;i<s.length();i++)
//						errorstr[i]=s[i];
//					error=true;
//					return NULL;
//			 }
//			 return buffer;
//		}*/
//		return NULL;
//	 };
//	virtual void Trasmitir( char*buffer,SOCKET s=NULL){
//		/*int n=send(t==ConnectionType::TCP_IP_SERVER?cliente:server,buffer,strlen(buffer),0);
//		 if(n==0)
//		 {
//		  string s("Error 0 ");
//	      errorstr=new char[s.length()+1];
//		  for(unsigned i=0;i<s.length();i++)
//			 errorstr[i]=s[i];
//		  error=true;
//		  return;
//		 }
//		  if(n==-1)
//		 {
//			string s("Error 1 ");
//			errorstr=new char[s.length()+1];
//			for(unsigned i=0;i<s.length();i++)
//				errorstr[i]=s[i];
//		    error=true;
//			return;
//		 }*/
//	 };
//	virtual void Select(){}
//	bool Error(){return error;};
//	bool EstaConectado(){return IsConectado;};
//	char* ErrorStr(){return errorstr;};
//	virtual char*getChar(){return new char(0);};
//	virtual unsigned getunsigned(){return 0;};
//	virtual char* ActionAfterError(){return new char(0);};
//	ConnectionType GetType(){return t;};
//	static void SetType(ConnectionType CT,Connection*conn){conn->t=CT;};
//	static char* GetMesage(Connection*conn){return conn->message;};
//};
//class TcP_ip_Server:public Connection
//{
//private:
//	fd_set descriptoresLectura;
//	SOCKET socketsClient[10];
//	struct timeval tv;
//	unsigned contClient;
//public:
//	bool salirThread;
//	TcP_ip_Server():Connection()
//	{
//		this->t=ConnectionType::TCP_IP_SERVER;
//		contClient=0;
//	}
//	~TcP_ip_Server()
//	{
//	   if(this->EstaConectado())
//	   {
//		   salirThread=false;
//		   this->CerrarSocket();
//	   }
//	};
//	void CloseConnection(){
//		CerrarSocket();
//	}
//	void CerrarSocket()
//	{
//		for(unsigned i=0;i<contClient;i++)
//			closesocket(socketsClient[i]);
//		WSACleanup();
//		IsConectado=false;
//	} 
//	bool inicializa(const char* Ip, unsigned long Port)
//	 {
//		WSAStartup(MAKEWORD(2,0),&wsData);
//		if((server=socket(AF_INET,SOCK_STREAM,0))<0)
//		{
//			this->error=true;
//			string s("Error 1 ");
//			errorstr=new char[s.length()+1];
//			for(unsigned i=0;i<s.length();i++)
//				 errorstr[i]=s[i];
//			CerrarSocket();
//			return false;
//		}
//		serveraddr.sin_addr.s_addr=inet_addr((const char*)Ip);   //INADDR_ANY;
//		serveraddr.sin_family=AF_INET;
//		serveraddr.sin_port=htons((u_short)Port);
//		if(::bind(server,(SOCKADDR*)&serveraddr,sizeof(serveraddr))!=0)
//		{
//			this->error=true;
//			string s("Error 2 ");
//			errorstr=new char[s.length()+1];
//			for(unsigned i=0;i<s.length();i++)
//				 errorstr[i]=s[i];
//			CerrarSocket();
//			return false;
//	   }
//		if(listen(server,0)!=0)
//		{
//			this->error=true;
//			string s("Error 3 ");
//			errorstr=new char[s.length()+1];
//			for(unsigned i=0;i<s.length();i++)
//				 errorstr[i]=s[i];
//			CerrarSocket();
//			return false;
//		}
//
//		error=false;
//		IsConectado=true;
//		this->ip=new char[strlen(Ip)+1];
//	    this->ip[strlen(Ip)]=0;
//	    for(unsigned i=0;i<strlen(Ip);i++)
//	   	   this->ip[i]=Ip[i];
//		this->Port=Port;
//		
//		return true;
//	 
//	 }
//	void Trasmitir(char*buffer,SOCKET s){
//		int n=-2;
//		if(s!=NULL)
//		{
//				n=send(s,buffer,strlen(buffer),0);
//		}
//		else
//		{
//				for(unsigned i=0;i<contClient;i++)
//					Trasmitir(buffer,socketsClient[i]);
//		}
//		 if(n==0)
//		 {
//				string s("Error 0 ");
//				errorstr=new char[s.length()+1];
//				for(unsigned i=0;i<s.length();i++)
//					errorstr[i]=s[i];
//				error=true;
//				return;
//		  }
//		  if(n==-1)
//		  {
//				string s("Error 1 ");
//				errorstr=new char[s.length()+1];
//				for(unsigned i=0;i<s.length();i++)
//					errorstr[i]=s[i];
//				error=true;
//				return;
//		  }
//	 };
//	char*getChar(){return ip;};
//	unsigned getunsigned(){return Port;};
//	/*char* ActionAfterError()
//	{
//		if(error=true)
//		{
//		   return ConnectClient();
//		}
//		return "No habia un error";
//	};*/
//	/*char* ConnectClient()
//	{
//		int clientaddrSize=sizeof(clientaddr);
//		   if((cliente=accept(server,(SOCKADDR*)&clientaddr,&clientaddrSize))<0)
//		   {
//			  this->error=true;
//			  this->errorstr="Error al conectar un cliente";
//			  return this->errorstr;
//		   }
//		   this->message="Cliente Conectado";
//		   error=false;
//		   return this->message;
//	}*/
//	void Select(){
//		tv.tv_sec=5;
//		tv.tv_usec=500000;
//		salirThread=true;
//		cout<<"Esperando clientes"<<endl;
//		m.lock();
//		while(salirThread)
//		{
//			FD_ZERO(&descriptoresLectura);
//			FD_SET(server,&descriptoresLectura);
//			for (unsigned i=0; i<contClient; i++)
//				FD_SET(socketsClient[i],&descriptoresLectura);
//			m.unlock();
//			select(server,&descriptoresLectura,NULL,NULL,NULL);
//			if(!salirThread)
//				return;
//			m.lock();
//			if(FD_ISSET(server,&descriptoresLectura))
//			{
//				SOCKET client;
//				int clientaddrSize=sizeof(clientaddr);
//				if((client=accept(server,(SOCKADDR*)&clientaddr,&clientaddrSize))<0)
//				{
//				   this->error=true;
//				   this->errorstr="Error al conectar un cliente";
//				   cout<<this->errorstr<<endl;
//				}
//				else
//				{
//					string s("Cliente Conectado:");
//					this->message=new char[s.length()+1];
//					this->message[s.length()]=0;
//					for(unsigned i=0;i<s.length();i++)
//						this->message[i]=s.c_str()[i];
//					cout<<this->message;
//					socketsClient[contClient++]=client;
//					cout<<client<<endl;;
//				}
//			}
//			else
//			{
//				for(unsigned i=0;i<contClient;i++)
//				{
//					memset(buffer,0,sizeof(buffer));
//					int n=recv(socketsClient[i],buffer,255,0);
//					switch(n)
//					{
//					case 0:
//						cout<<"Cliente desconectado"<<endl;
//						for(unsigned ii=i;ii<contClient-1;i++)
//							socketsClient[ii]=socketsClient[ii+1];
//						contClient--;
//						break;
//					case -1:
//						cout<<"Error al leer al cliente"<<endl;
//						for(unsigned ii=i;ii<contClient-1;i++)
//							socketsClient[ii]=socketsClient[ii+1];
//						contClient--;
//						break;
//					default:
//						buffer[(unsigned)n]=0;
//						cout<<buffer<<endl;
//						break;
//					}
//				}
//			}
//			
//		}
//	}
//};
//class TcP_ip_Client:public Connection
//{
//public:
//	TcP_ip_Client():Connection()
//	{
//		this->t=ConnectionType::TCP_IP_CLIENT;
//	}
//	~TcP_ip_Client(){
//	if(this->EstaConectado())
//			this->CerrarSocket();
//	};
//	void CloseConnection(){
//		CerrarSocket();
//	}
//	void Send()
//	{
//		cin>>this->buffer;
//		cout<<endl;
//		send(server,buffer,sizeof(buffer),0);
//		memset(buffer,0,sizeof(buffer));
//	}
//	void CerrarSocket()
//	{
//		closesocket(server);
//		WSACleanup();
//		IsConectado=false;	
//	}
//	bool inicializa(const char* Ip, unsigned long Port)
//	{
//	    WSAStartup(MAKEWORD(2,0),&wsData);
//		if((server=socket(AF_INET,SOCK_STREAM,0))<0)
//		{
//			this->error=true;
//			string s("Error 0 ");
//			errorstr=new char[s.length()+1];
//			for(unsigned i=0;i<s.length();i++)
//				 errorstr[i]=s[i];
//			CerrarSocket();
//			return false;
//		}
//		serveraddr.sin_addr.s_addr=inet_addr((const char*)Ip);
//		serveraddr.sin_family=AF_INET;
//		serveraddr.sin_port=htons((u_short)Port);
//		if(connect(server,(SOCKADDR*)&serveraddr,sizeof(serveraddr))<0)
//		 {
//			string s("C_Error 1 :"+string(Ip)+":"+to_string(Port));
//			errorstr=new char[s.length()+1];
//			for(unsigned i=0;i<s.length();i++)
//				 errorstr[i]=s[i];
//			this->error=true;
//			CerrarSocket();
//			return false;
//		 }
//		else
//		{
//
//		string s(string(Ip)+":"+to_string(Port));
//		errorstr=new char[s.length()+1];
//		for(unsigned i=0;i<s.length();i++)
//		    errorstr[i]=s[i];
//		}
//
//
//		error=false;
//		IsConectado=true;
//		this->ip=new char[strlen(Ip)+1];
//	    this->ip[strlen(Ip)]=0;
//	    for(unsigned i=0;i<strlen(Ip);i++)
//	   	   this->ip[i]=Ip[i];
//		this->Port=Port;
//
//		return true;
//	};
//	char* Recibir()
//	{
//		if(EstaConectado())
//		{
//			 memset(buffer,0,sizeof(buffer));
//			 int n=recv(server,buffer,255,0);
//			 if(n==0)
//			 {
//				 string s("Error 0 ");
//				 errorstr=new char[s.length()+1];
//				 for(unsigned i=0;i<s.length();i++)
//					 errorstr[i]=s[i];
//				 error=true;
//				 return NULL;
//			 }
//			 if(n==-1)
//			 {
//					string s("C_Error 1 ");
//					errorstr=new char[s.length()+1];
//					for(unsigned i=0;i<s.length();i++)
//						errorstr[i]=s[i];
//					error=true;
//					return NULL;
//			 }
//			 buffer[n]=0;
//			 return buffer;
//		}
//		return NULL;
//	 };
//	void Trasmitir( char*buffer,SOCKET s){
//		int n=send(server,buffer,strlen(buffer),0);
//		 if(n==0)
//		 {
//		  string s("Error 0 ");
//	      errorstr=new char[s.length()+1];
//		  for(unsigned i=0;i<s.length();i++)
//			 errorstr[i]=s[i];
//		  error=true;
//		  return;
//		 }
//		  if(n==-1)
//		 {
//			string s("Error 1 ");
//			errorstr=new char[s.length()+1];
//			for(unsigned i=0;i<s.length();i++)
//				errorstr[i]=s[i];
//		    error=true;
//			return;
//		 }
//	 };
//	char*getChar(){return ip;};
//	unsigned getunsigned(){return Port;};
//	char* ActionAfterError()
//	{
//	  if(error=true)
//		{
//			if(inicializa(this->ip,this->Port))
//				return this->message;
//			else
//				return this->errorstr;
//	    }
//	  return "NULL";
//	}
//};
//class PuertoSerie:public Connection
//{
//	
//private:
//	HANDLE handler;
//	char*Puerto;
//	unsigned long Speed;
//public:
//	PuertoSerie():Connection()
//	{
//		Puerto=new char[1];
//		this->t=ConnectionType::SERIAL_PORT;
//	};
//	//PuertoSerie(System::String^PuertoCom, unsigned long Velocidad);
//	~PuertoSerie()
//    {
//		CloseConnection();
//    }
//	void CloseConnection()
//	{
//		delete[]Puerto;
//		if(IsConectado)
//		{
//		   IsConectado=false;
//		   CloseHandle(handler);
//	    }
//	
//	}
//	bool inicializa(const char* PuertoCom, unsigned long Velocidad)
//{
//	handler=CreateFile(PuertoCom,GENERIC_READ | GENERIC_WRITE,NULL,NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
//	if (handler==INVALID_HANDLE_VALUE)
//	{
//		string s("C_Error 0 :"+string(PuertoCom)+":"+to_string(Velocidad));
//		errorstr=new char[s.length()+1];
//		for(unsigned i=0;i<s.length();i++)
//			errorstr[i]=s[i];
//		error=true;
//		return false;
//	}
//	DCB ParametrosTxSerie;
//	if (!GetCommState(handler,&ParametrosTxSerie))
//	{
//		string s("Error 1 :"+string(PuertoCom)+":"+to_string(Velocidad));
//		errorstr=new char[s.length()+1];
//		for(unsigned i=0;i<s.length();i++)
//				errorstr[i]=s[i];
//		return false;
//	}
//	ParametrosTxSerie.DCBlength=sizeof(DCB);
//	ParametrosTxSerie.BaudRate=Velocidad;
//	ParametrosTxSerie.ByteSize=8;
//	ParametrosTxSerie.StopBits=TWOSTOPBITS;
//	ParametrosTxSerie.Parity=(BYTE)PARITY_NONE;
//	if(!SetCommState(handler,&ParametrosTxSerie))
//	{
//		string s("Error 2 :"+string(PuertoCom)+":"+to_string(Velocidad));
//		errorstr=new char[s.length()+1];
//		for(unsigned i=0;i<s.length();i++)
//			errorstr[i]=s[i];
//		error=true;
//		return false;
//	}
//	IsConectado=true;
//	PurgeComm(handler,PURGE_RXCLEAR|PURGE_TXCLEAR);
//	error=false;
//	this->Puerto=new char[strlen(PuertoCom)+1];
//	this->Puerto[strlen(PuertoCom)]=0;
//	for(unsigned i=0;i<strlen(PuertoCom);i++)
//		this->Puerto[i]=PuertoCom[i];
//	this->Speed=Velocidad;
//	string s(string(PuertoCom)+":"+to_string(Velocidad));
//	errorstr=new char[s.length()+1];
//	for(unsigned i=0;i<s.length();i++)
//			errorstr[i]=s[i];
//	return true;
//}
//	char* Recibir()
//	{
//	char*cadena=NULL;
//	if(EstaConectado())
//	{
//		DWORD leidos;
//		COMSTAT cs;
//		if(ClearCommError(handler,&leidos,&cs)==0)
//		{
//			this->error=true;
//			string s("Error 0 ");
//			errorstr=new char[s.length()+1];
//			for(unsigned i=0;i<s.length();i++)
//				 errorstr[i]=s[i];
//			return NULL;
//		}
//		leidos=0;
//		if(cs.cbInQue)
//		{
//			cadena=new char[cs.cbInQue+3];
//			cadena[cs.cbInQue]=0;
//			ReadFile(handler,cadena,cs.cbInQue,&leidos,NULL);
//			return cadena;
//		}
//	}
//	return cadena;
//	};
//	void Trasmitir(char *oBuffer)
//{
//	DWORD iBytesWritten;
//	iBytesWritten=0;
//	WriteFile(handler,oBuffer,strlen(oBuffer),&iBytesWritten,NULL);
//}
//	//void Trasmitir(System::String^data);
//	bool Error(){return error;};
//	char* ErrorStr(){return errorstr;};
//	char*getChar(){return Puerto;};
//	unsigned getunsigned(){return Speed;};
//};
enum ConnectionType
{
 CONNECTION,SOCKET_SERVER,SOCKET_CLIENT,SERIAL_PORT,WEBSOCKET_CLIENT
};
class Connection
{
protected:
	ConnectionType t;
	bool IsConectado;
	bool error;
	char*errorstr,*message; 
public:
	Connection(){
		t=ConnectionType::CONNECTION;
		IsConectado=error=false;
		errorstr=new char[1];
		errorstr[0]=0;
		message=new char[1];
		message[0]=0;
	};
	virtual ~Connection()
	{
		delete[]errorstr;
		delete[]message;
	};
	virtual void CloseConnection(){};
	virtual bool inicializa(const char*Ip, unsigned long Port){return false;};
	virtual char* Recibir()
	{
		/*if(EstaConectado())
		{
			 memset(buffer,0,sizeof(buffer));
			 int n=recv(t==ConnectionType::SOCKET_SERVER?cliente:server,buffer,sizeof(buffer),0);
			 if(n==0)
			 {
				 string s("Error 0 ");
				 errorstr=new char[s.length()+1];
				 for(unsigned i=0;i<s.length();i++)
					 errorstr[i]=s[i];
				 error=true;
				 return NULL;
			 }
			 if(n==-1)
			 {
					string s("C_Error 1 ");
					errorstr=new char[s.length()+1];
					for(unsigned i=0;i<s.length();i++)
						errorstr[i]=s[i];
					error=true;
					return NULL;
			 }
			 return buffer;
		}*/
		return NULL;
	 };
	virtual void Trasmitir( char*buffer,SOCKET s=NULL){
		/*int n=send(t==ConnectionType::SOCKET_SERVER?cliente:server,buffer,strlen(buffer),0);
		 if(n==0)
		 {
		  string s("Error 0 ");
	      errorstr=new char[s.length()+1];
		  for(unsigned i=0;i<s.length();i++)
			 errorstr[i]=s[i];
		  error=true;
		  return;
		 }
		  if(n==-1)
		 {
			string s("Error 1 ");
			errorstr=new char[s.length()+1];
			for(unsigned i=0;i<s.length();i++)
				errorstr[i]=s[i];
		    error=true;
			return;
		 }*/
	 };
	virtual char*getChar(){return nullptr;};
	virtual unsigned getunsigned(){return 0;};
	bool Error(){return error;};
	bool EstaConectado(){return IsConectado;};
	char* ErrorStr(){return errorstr;};
	ConnectionType GetType(){return t;};
	static void SetType(ConnectionType CT,Connection*conn){conn->t=CT;};
	static char* GetMesage(Connection*conn){
		string s(string(conn->getChar())+":"+to_string(conn->getunsigned()));
		delete[]conn->message;
		conn->message=new char[s.length()+1];
		conn->message[s.length()]=0;
		for(unsigned i=0;i<s.length();i++)
			conn->message[i]=s[i];
		return conn->message;
		
	};
};
class Socket_Client:public Connection
{
	
protected:
	WSADATA wsData;
	SOCKET server;
	SOCKADDR_IN serveraddr,clientaddr;
	string bufers;
	char*ip;
	unsigned Port;
	bool _0;
public:
	Socket_Client():Connection()
	{
		this->t=ConnectionType::SOCKET_CLIENT;
		ip=new char[1];
		bool _0=false;
	}
	~Socket_Client(){
		delete[]ip;
		this->CloseConnection();
	};
	virtual void CloseConnection(){
		if(EstaConectado())
		{
			closesocket(server);
			WSACleanup();
			IsConectado=false;
		}
	}
	virtual bool inicializa(const char* Ip, unsigned long Port)
	{
	    WSAStartup(MAKEWORD(2,0),&wsData);
		if((server=socket(AF_INET,SOCK_STREAM,0))<0)
		{
			this->error=true;
			string s("Error 0 ,socket no creado");
			delete[]errorstr;
			errorstr=new char[s.length()+1];
			errorstr[s.length()]=0;
			for(unsigned i=0;i<s.length();i++)
				 errorstr[i]=s[i];
			cout<<errorstr<<endl;
			return false;
		}
		serveraddr.sin_addr.s_addr=inet_addr((const char*)Ip);
		serveraddr.sin_family=AF_INET;
		serveraddr.sin_port=htons((u_short)Port);
		if(connect(server,(SOCKADDR*)&serveraddr,sizeof(serveraddr))<0)
		 {
			string s("Error 1 : no se puedo conectar con:"+string(Ip)+":"+to_string(Port));
			delete[]errorstr;
			errorstr=new char[s.length()+1];
			errorstr[s.length()]=0;
			for(unsigned i=0;i<s.length();i++)
				 errorstr[i]=s[i];
			this->error=true;
			cout<<errorstr<<endl;
			return false;
		 }
		/*else
		{
		
		string s(string(Ip)+":"+to_string(Port));
		delete[]errorstr;
		errorstr=new char[s.length()+1];
		errorstr[s.length()]=0;
		for(unsigned i=0;i<s.length();i++)
		    errorstr[i]=s[i];
		}*/
		IsConectado=true;
		char toSend[3];
		toSend[0]=(char)39;
		toSend[1]=1;
		toSend[2]=0;
		this->Trasmitir(toSend);
		fd_set descriptoresLectura1;
		struct timeval tv1;
		tv1.tv_sec=3;
		tv1.tv_usec=55555;
		FD_ZERO(&descriptoresLectura1);
		FD_SET(server,&descriptoresLectura1);
		select(server,&descriptoresLectura1,NULL,NULL,&tv1);
		bool err=true;
		char*toReciv;
		if(FD_ISSET(server,&descriptoresLectura1))
		{
			toReciv=Recibir();
			if(toReciv!=NULL)
				if(toReciv[0]==(char)39)
				err=false;
		}
		if(err)
		{
			string s("Error : no se puedo atenticar como Windows con:"+string(Ip)+":"+to_string(Port));
			delete[]errorstr;
			errorstr=new char[s.length()+1];
			errorstr[s.length()]=0;
			for(unsigned i=0;i<s.length();i++)
				 errorstr[i]=s[i];
			this->error=true;
			cout<<errorstr<<endl;
			CloseConnection();
			return false;
		}
		error=false;
		delete[]ip;
		this->ip=new char[strlen(Ip)+1];
	    this->ip[strlen(Ip)]=0;
	    for(unsigned i=0;i<strlen(Ip);i++)
	   	   this->ip[i]=Ip[i];
		this->Port=Port;

		return true;
	};
	virtual char* Recibir()
	{
		if(EstaConectado())
		{
			 /*memset(buffer,0,sizeof(buffer));
			 int n=recv(server,buffer,1024,0);
			 if(n==0)
			 {
				 string s("Error 0, dato no recivido, conexion cerrada");
				 delete[]errorstr;
				 errorstr=new char[s.length()+1];
				 errorstr[s.length()]=0;
				 for(unsigned i=0;i<s.length();i++)
					 errorstr[i]=s[i];
				 error=true;
				 cout<<errorstr<<endl;
				 CloseConnection();
				 return NULL;
			 }*/
			 bufers.clear();
			 char BuFFeR[1024];
			 fd_set descriptoresLecturaReciv;
			 struct timeval tvReciv;
			 tvReciv.tv_sec=0;
			 tvReciv.tv_usec=55555;
			 int n=recv(server,BuFFeR,1023,0);
			 if(n!=0&&n!=-1)
			 {
				BuFFeR[n]=0;
				bufers+=BuFFeR;
				if(bufers.length()!=n)
				{
					for(unsigned i=0;i<n;i++)
						if(BuFFeR[i]==0 && i!=n-1)
						{
							//BuFFeR[i]=(char)1;
							//bool _0=true;
							bufers.clear();
							for(unsigned ii=0;ii<n;ii++)
							{
								if(i==ii)
									bufers+=(char)0;
								else
									bufers+=BuFFeR[ii];
							}	
							//bufers+=BuFFeR;
							break;
						}
				}
				do
				{
					FD_ZERO(&descriptoresLecturaReciv);
					FD_SET(server,&descriptoresLecturaReciv);
					select(server,&descriptoresLecturaReciv,NULL,NULL,&tvReciv);
					if(FD_ISSET(server,&descriptoresLecturaReciv))
					{
						memset(BuFFeR,0,sizeof(BuFFeR));
						int m=recv(server,BuFFeR,1023,0);
						if(m==0||m==-1)
							break;
						BuFFeR[m]=0;
						n+=m;
						bufers+=BuFFeR;
					}
					else
						break;	
				}while(true);
			 }
			  if(n==0)
			 {
				 string s("Error 0, dato no recivido, conexion cerrada");
				 delete[]errorstr;
				 errorstr=new char[s.length()+1];
				 errorstr[s.length()]=0;
				 for(unsigned i=0;i<s.length();i++)
					 errorstr[i]=s[i];
				 error=true;
				 cout<<errorstr<<endl;
				 CloseConnection();
				 return NULL;
			 }
			 if(n==-1)
			 {
					string s("Error 1, Conexion perdida");
					delete[]errorstr;
					errorstr=new char[s.length()+1];
					errorstr[s.length()]=0;
					for(unsigned i=0;i<s.length();i++)
						errorstr[i]=s[i];
					error=true;
					cout<<errorstr<<endl;
					CloseConnection();
					return NULL;
			 }
			 else if(BuFFeR==NULL)
				 return NULL;
			 else if(n>0)
			 {
				 return (char*)bufers.c_str();
			 }
		}
		return NULL;
	 };
	virtual void Trasmitir( char*buffer,SOCKET s=NULL){
		if(EstaConectado())
		{
			 int n=send(server,buffer,strlen(buffer),0);
			 if(n==0)
			 {
			  string s("Error 0 , dato no enviado, conexion cerrada");
			  cout<<errorstr<<endl;
			  error=true;
			  CloseConnection();
			  return;
			 }
			  if(n==-1)
			 {
				string s("Error 1, Conexion Perdida");
				error=true;
				cout<<errorstr<<endl;
				CloseConnection();
				return;
			 }
		}
	 };
	virtual char*getChar(){return ip;};
	unsigned getunsigned(){return Port;};
};
class WebSocket_Client:public Socket_Client
{
private:
	char*Hostname;
	char MaskKey[4];
	bool FirstConnect;
	bool BinaryData;
public:
	WebSocket_Client():Socket_Client()
	{
		this->t=ConnectionType::WEBSOCKET_CLIENT;
		Hostname=new char[1];
		FirstConnect=true;
		MaskKey[0]='A';
		MaskKey[1]='B';
		MaskKey[2]='C';
		MaskKey[3]='D';
		BinaryData=false;
	}
	~WebSocket_Client()
	{
		delete[]Hostname;
	}
	bool inicializa(const char* HostName, unsigned long Port)
	{
	    WSAStartup(MAKEWORD(2,0),&wsData);
		if((server=socket(AF_INET,SOCK_STREAM,0))<0)
		{
			this->error=true;
			string s("Error 0 ,socket no creado");
			delete[]errorstr;
			errorstr=new char[s.length()+1];
			errorstr[s.length()]=0;
			for(unsigned i=0;i<s.length();i++)
				 errorstr[i]=s[i];
			cout<<errorstr<<endl;
			return false;
		}
		struct hostent* host;
		host=gethostbyname(HostName);
		if(!host)
		{
			this->error=true;
			string s("Error 0 ,Host no accesible");
			delete[]errorstr;
			errorstr=new char[s.length()+1];
			errorstr[s.length()]=0;
			for(unsigned i=0;i<s.length();i++)
				 errorstr[i]=s[i];
			cout<<errorstr<<endl;
			return false;
		}
		serveraddr.sin_addr.s_addr=*(u_long*)host->h_addr_list[0];
		serveraddr.sin_family=AF_INET;
		serveraddr.sin_port=htons((u_short)Port);
		if(connect(server,(SOCKADDR*)&serveraddr,sizeof(serveraddr))<0)
		 {
			string s("Error 1 : no se puedo conectar con:"+string(HostName)+":"+to_string(Port));
			delete[]errorstr;
			errorstr=new char[s.length()+1];
			errorstr[s.length()]=0;
			for(unsigned i=0;i<s.length();i++)
				 errorstr[i]=s[i];
			this->error=true;
			cout<<errorstr<<endl;
			return false;
		 }
		IsConectado=true;
		string s("GET /chat HTTP/1.1 \r\n");
		s+="Host: ";
		s+=HostName;
		s+=":";
		s+=to_string(Port);
		s+=" \r\n"
			"Upgrade: websocket \r\n"
			"Connection: Upgrade \r\n"
			"Sec-WebSocket-Key: dGhlIHNhbXbsZSBub25jZQ== \r\n"             
			"Sec-WebSocket-Version: 13 \r\n"
			"\r\n";
		this->Trasmitir((char*)s.c_str());
		fd_set descriptoresLectura;
		struct timeval tv;
		tv.tv_sec=1;
		tv.tv_usec=55555;
		FD_ZERO(&descriptoresLectura);
		FD_SET(server,&descriptoresLectura);
		select(server,&descriptoresLectura,NULL,NULL,&tv);
		string buff;
		if(FD_ISSET(server,&descriptoresLectura))
			buff+=this->Recibir();
		if(FirstConnect&&buff.length())
		{
			if(!strcmp((char*)buff.substr(0,strlen("HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\n")).c_str(),"HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\n"))
			{
				FirstConnect=false;
			}
		}
		if(FirstConnect)
		{
			string s("Error: no se puedo conectar con:"+string(HostName)+":"+to_string(Port));
			delete[]errorstr;
			errorstr=new char[s.length()+1];
			errorstr[s.length()]=0;
			for(unsigned i=0;i<s.length();i++)
					errorstr[i]=s[i];
			this->error=true;
			cout<<errorstr<<endl;
			CloseConnection();
			return false;
		}
		error=false;
		char toSend[3];
		toSend[0]=39;
		toSend[1]=1;
		toSend[2]=0;
		this->Trasmitir(toSend);
		fd_set descriptoresLectura1;
		struct timeval tv1;
		tv1.tv_sec=3;
		tv1.tv_usec=55555;
		FD_ZERO(&descriptoresLectura1);
		FD_SET(server,&descriptoresLectura1);
		select(server,&descriptoresLectura1,NULL,NULL,&tv1);
		bool err=true;
		char*toReciv;
		if(FD_ISSET(server,&descriptoresLectura1))
		{
			toReciv=Recibir();
			if(toReciv!=NULL)
				if(toReciv[0]==(char)39)
				err=false;
		}
		if(err)
		{
			string s("Error : no se puedo atenticar como Windows con:"+string(HostName)+":"+to_string(Port));
			delete[]errorstr;
			errorstr=new char[s.length()+1];
			errorstr[s.length()]=0;
			for(unsigned i=0;i<s.length();i++)
				 errorstr[i]=s[i];
			this->error=true;
			cout<<errorstr<<endl;
			CloseConnection();
			return false;
		}





		delete[]this->Hostname;
		this->Hostname=new char[strlen(HostName)+1];
	    this->Hostname[strlen(HostName)]=0;
	    for(unsigned i=0;i<strlen(HostName);i++)
	   	   this->Hostname[i]=HostName[i];
		
		char*Ip=inet_ntoa(serveraddr.sin_addr);
		delete[]ip;
		this->ip=new char[strlen(Ip)+1];
	    this->ip[strlen(Ip)]=0;
	    for(unsigned i=0;i<strlen(Ip);i++)
	   	   this->ip[i]=Ip[i];
		this->Port=Port;

		return true;
	};
	void Trasmitir(char*BuFFeR,SOCKET s=NULL){
		if(EstaConectado())
		{
			string ToSend(BuFFeR);
			if(!FirstConnect)
			{//10000010
				ToSend.clear();
				if(DataProcessor::CodigoESE(BuFFeR[0],BuFFeR[1])||DataProcessor::CodigoServer(BuFFeR[0],BuFFeR[1]))
					ToSend+=(char)130;
				else
					ToSend+=(char)129;
				DataUnion du;
				du.SetUnsigned(strlen(BuFFeR));
				unsigned uns=du.u.Unsigned;
				if(uns<=125)
				{
					DataProcessor::SetBit(du.u.Char,7,true);
					ToSend+=du.u.Char;
				}				
				else if(uns<65536)
				{
					ToSend+=(char)254;
					ToSend+=du.u.String[1];
					ToSend+=du.u.String[0];
				}
				else
				{
					ToSend+=(char)255;
					for(int i=7;i>=0;i--)
						ToSend+=du.u.String[(unsigned)i];
				}
				//FirstByte
				//ToSend+=DataProcessor::SetByte("10000001");
				//string MaskAndLength;
				////Length
				//if(strlen(BuFFeR)<=125)
				//{
				//	char Lengthstr[8];
				//	_itoa_s((int)strlen(BuFFeR),Lengthstr,2);
				//	for(unsigned i=0;i<8-strlen(Lengthstr);i++)
				//		MaskAndLength+='0';
				//	MaskAndLength+=Lengthstr;
				//	MaskAndLength[0]='1';
				//}
				//else if(strlen(BuFFeR)<=512)
				//{
				//	ToSend+=DataProcessor::SetByte("11111110");
				//	char Lengthstr[16];
				//	_itoa_s((int)strlen(BuFFeR),Lengthstr,2);
				//	for(unsigned i=0;i<16-strlen(Lengthstr);i++)
				//		MaskAndLength+='0';
				//	MaskAndLength+=Lengthstr;
				//}
				//else
				//{
				//	ToSend+=DataProcessor::SetByte("11111111");
				//	char Lengthstr[64];
				//	_itoa_s((int)strlen(BuFFeR),Lengthstr,2);
				//	for(unsigned i=0;i<8-strlen(Lengthstr);i++)
				//		MaskAndLength+='0';
				//	MaskAndLength+=Lengthstr;
				//}
				//ToSend+=DataProcessor::SetByte((char*)MaskAndLength.c_str());
				//Codific
				for(unsigned i=0;i<4;i++)
					ToSend+=MaskKey[i];
				//char*toCodiF=new char[strlen(BuFFeR)+1];
				//toCodiF[strlen(BuFFeR)]=0;
				for(unsigned i=0;i<strlen(BuFFeR);i++)
					ToSend+=(BuFFeR[i]^MaskKey[i%4]);
				//ToSend+=toCodiF;
				//delete[]toCodiF;
			 }
			 //Send
			 int n=send(server,ToSend.c_str(),ToSend.length(),0);
			 if(n==0)
			 {

			     string s("Error 0 , dato no enviado, conexion cerrada");
				 cout<<errorstr<<endl;
				 error=true;
				 CloseConnection();
				 return;
			 }
			  if(n==-1)
			 {
				 string s("Error 1, Conexion Perdida");
				 error=true;
				 cout<<errorstr<<endl;
				 CloseConnection();
				 return;
			 }
		}
	 };
	char* Recibir()
	{
		//if(EstaConectado())
		//{
		//	 /*char MyBuffer[1024];
		//	 int n=recv(server,MyBuffer,1023,0);*/
		//	 bufers.clear();
		//	 char BuFFeR[1024];
		//	 fd_set descriptoresLecturaReciv;
		//	 struct timeval tvReciv;
		//	 tvReciv.tv_sec=0;
		//	 tvReciv.tv_usec=55555;
		//	 int n=recv(server,BuFFeR,1023,0);
		//	 if(n!=0&&n!=-1)
		//	 {
		//		BuFFeR[n]=0;
		//		do
		//		{
		//			bufers+=BuFFeR;
		//			FD_ZERO(&descriptoresLecturaReciv);
		//			FD_SET(server,&descriptoresLecturaReciv);
		//			select(server,&descriptoresLecturaReciv,NULL,NULL,&tvReciv);
		//			if(FD_ISSET(server,&descriptoresLecturaReciv))
		//			{
		//				memset(BuFFeR,0,sizeof(BuFFeR));
		//				int m=recv(server,BuFFeR,1023,0);
		//				if(m==0||m==-1)
		//					break;
		//				BuFFeR[m]=0;
		//				n+=m;
		//				bufers+=BuFFeR;
		//			}
		//			else
		//				break;	
		//		}while(true);
		//	 }
		//	 if(n==0)
		//	 {
		//		 string s("Error 0, dato no recivido, conexion cerrada");
		//		 delete[]errorstr;
		//		 errorstr=new char[s.length()+1];
		//		 errorstr[s.length()]=0;
		//		 for(unsigned i=0;i<s.length();i++)
		//			 errorstr[i]=s[i];
		//		 error=true;
		//		 cout<<errorstr<<endl;
		//		 CloseConnection();
		//		 return NULL;
		//	 }
		//	 if(n==-1)
		//	 {
		//			string s("Error 1, Conexion perdida");
		//			delete[]errorstr;
		//			errorstr=new char[s.length()+1];
		//			errorstr[s.length()]=0;
		//			for(unsigned i=0;i<s.length();i++)
		//				errorstr[i]=s[i];
		//			error=true;
		//			cout<<errorstr<<endl;
		//			CloseConnection();
		//			return NULL;
		//	 }
		//	 else if(BuFFeR==NULL)
		//		 return NULL;
		//	 else if(n>0)
		//	 {
		//		//MyBuffer[n]=0;
		//		if(!FirstConnect)
		//		{
		//			ProccesData((char*)string(bufers).c_str());
		//			 return (char*)bufers.c_str();
		//		}
		//		return (char*)bufers.c_str();
		//	 }
		//}
		if(Socket_Client::Recibir()!=NULL)
		{
			if(!FirstConnect)
				{
					ProccesData(string(bufers));
				}
				return (char*)bufers.c_str();
		}
		return NULL;
	 };
	char*getChar(){return Hostname;};
	void ProccesData(string Buffer)
	{
		string sC(Buffer);
		string s(Buffer);
		//char*Data;
		bufers.clear();
		for(unsigned j=0;j<s.length();j++)
		{
			string data;
			if(2>sC.length())
			{
				bufers.clear();
				return;
			}
			bool fin=DataProcessor::GetBit(s[j],7);
			bool Mask=DataProcessor::GetBit(s[j+1],7);
			DataProcessor::SetBit(s[j+1],7,false);
			//Length Y MaskKey
			DataUnion du;
			du.SetChar(s[j+1]);
			//unsigned length=DataProcessor::GetDataByBinary(&s[1],1);
			unsigned length=du.u.Unsigned;
			sC=sC.substr(2,sC.length()-1);
			char MasksKeY[4];
			if(length<=125)
			{
				if(Mask)
				{
					if(4>sC.length())
					{
						bufers.clear();
						return;
					}
					MasksKeY[0]=s[j+2];
					MasksKeY[1]=s[j+3];
					MasksKeY[2]=s[j+4];
					MasksKeY[3]=s[j+5];
					sC=sC.substr(4,sC.length()-1);
				}
				if(length>sC.length())
				{
					bufers.clear();
					return;
				}
				for(unsigned i=0;i<length;i++)
					data+=s[j+i+2];
				sC=sC.substr(length,sC.length()-1);
			}
			else if(length==126)
			{
				if(2>sC.length())
				{
					bufers.clear();
					return;
				}
				string ss;
				ss+=s[j+3];
				//if(_0&&s[j+2]==1)
				//{
				//	ss+=(char)0;
				//	_0=false;
				//}
				//else
				ss+=s[j+2];
				sC=sC.substr(2,sC.length()-1);
				//unsigned lengthS=(unsigned)DataProcessor::GetDataByBinary((char*)ss.c_str(),2);
				du.SetStr(ss.c_str(),2,sizeof(short));
				unsigned lengthS=du.u.Unsigned;
				if(Mask)
				{
					if(4>sC.length())
					{
						bufers.clear();
						return;
					}
					MasksKeY[0]=s[j+4];
					MasksKeY[1]=s[j+5];
					MasksKeY[2]=s[j+6];
					MasksKeY[3]=s[j+7];
					sC=sC.substr(4,sC.length()-1);
				}
				if(lengthS>sC.length())
				{
					bufers.clear();
					return;
				}
				for(unsigned i=0;i<lengthS;i++)
					data+=s[j+(Mask?8:4)+i];
				sC=sC.substr(lengthS,sC.length()-1);
			}
			else
			{
				if(8>sC.length())
				{
					bufers.clear();
					return;
				}
				string ss;
				ss+=s[j+9];
				ss+=s[j+8];
				ss+=s[j+7];
				ss+=s[j+6];
				ss+=s[j+5];
				ss+=s[j+4];
				ss+=s[j+3];
				ss+=s[j+2];
				sC=sC.substr(8,sC.length()-1);
				//unsigned long long lengthS=DataProcessor::GetDataByBinary((char*)ss.c_str(),8);
				du.SetStr(ss.c_str(),2,sizeof(double));
				unsigned lengthS=(unsigned)du.u.Double;
				if(Mask)
				{
					if(4>sC.length())
					{
						bufers.clear();
						return;
					}
					MasksKeY[0]=s[j+10];
					MasksKeY[1]=s[j+11];
					MasksKeY[2]=s[j+12];
					MasksKeY[3]=s[j+13];
					sC=sC.substr(4,sC.length()-1);
				}
				if(lengthS>sC.length())
				{
					bufers.clear();
					return;
				}
				for(unsigned i=0;i<lengthS;i++)
					data+=s[j+(Mask?14:10)+i];
				sC=sC.substr(lengthS,sC.length()-1);
			}
			if(Mask)
				for(unsigned i=0;i<data.length();i++)
					bufers+=(char)(data[j+i]^MasksKeY[i%4]);
			else
				bufers+=data;
			j+=s.length()-sC.length()-1;
		}
	}
	void CloseConnection()
	{
		FirstConnect=true;
		Socket_Client::CloseConnection();
	}
};
class PuertoSerie:public Connection
{
	
private:
	HANDLE handler;
	char*Puerto;
	unsigned long Speed;
public:
	PuertoSerie():Connection()
	{
		Puerto=new char[1];
		this->t=ConnectionType::SERIAL_PORT;
	};
	//PuertoSerie(System::String^PuertoCom, unsigned long Velocidad);
	~PuertoSerie()
    {
		delete[]Puerto;
		CloseConnection();
    }
	void CloseConnection()
	{
		if(IsConectado)
		{
		   IsConectado=false;
		   CloseHandle(handler);
	    }
	
	}
	bool inicializa(const char* PuertoCom, unsigned long Velocidad)
{
	handler=CreateFile(PuertoCom,GENERIC_READ | GENERIC_WRITE,NULL,NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	if (handler==INVALID_HANDLE_VALUE)
	{
		string s("C_Error 0 :"+string(PuertoCom)+":"+to_string(Velocidad));
		delete[]errorstr;
		errorstr=new char[s.length()+1];
		errorstr[s.length()]=0;
		for(unsigned i=0;i<s.length();i++)
			 errorstr[i]=s[i];
		error=true;
		return false;
	}
	DCB ParametrosTxSerie;
	if (!GetCommState(handler,&ParametrosTxSerie))
	{
		string s("Error 1 :"+string(PuertoCom)+":"+to_string(Velocidad));
		delete[]errorstr;
		errorstr=new char[s.length()+1];
		errorstr[s.length()]=0;
		for(unsigned i=0;i<s.length();i++)
			errorstr[i]=s[i];
		error=true;
		return false;
	}
	ParametrosTxSerie.DCBlength=sizeof(DCB);
	ParametrosTxSerie.BaudRate=Velocidad;
	ParametrosTxSerie.ByteSize=8;
	ParametrosTxSerie.StopBits=TWOSTOPBITS;
	ParametrosTxSerie.Parity=(BYTE)PARITY_NONE;
	if(!SetCommState(handler,&ParametrosTxSerie))
	{
		string s("Error 2 :"+string(PuertoCom)+":"+to_string(Velocidad));
		delete[]errorstr;
		errorstr=new char[s.length()+1];
		errorstr[s.length()]=0;
		for(unsigned i=0;i<s.length();i++)
			errorstr[i]=s[i];
		error=true;
		return false;
	}
	IsConectado=true;
	PurgeComm(handler,PURGE_RXCLEAR|PURGE_TXCLEAR);
	error=false;
	delete[]this->Puerto;
	this->Puerto=new char[strlen(PuertoCom)+1];
	this->Puerto[strlen(PuertoCom)]=0;
	for(unsigned i=0;i<strlen(PuertoCom);i++)
		this->Puerto[i]=PuertoCom[i];
	this->Speed=Velocidad;
	return true;
}
	char* Recibir()
	{
		char*cadena=NULL;
		if(EstaConectado())
		{
			DWORD leidos;
			COMSTAT cs;
			if(ClearCommError(handler,&leidos,&cs)==0)
			{
				this->error=true;
				string s("Error 0 ");
				delete[]errorstr;
				errorstr=new char[s.length()+1];
				errorstr[s.length()]=0;
				for(unsigned i=0;i<s.length();i++)
					 errorstr[i]=s[i];
				return cadena;
			}
			leidos=0;
			if(cs.cbInQue)
			{
				cadena=new char[cs.cbInQue+3];
				cadena[cs.cbInQue]=0;
				ReadFile(handler,cadena,cs.cbInQue,&leidos,NULL);
				return cadena;
			}
		}
		return cadena;
	};
	void Trasmitir(char *oBuffer,SOCKET s=NULL)
	{
	DWORD iBytesWritten;
	iBytesWritten=0;
	WriteFile(handler,oBuffer,strlen(oBuffer),&iBytesWritten,NULL);
	}
	//void Trasmitir(System::String^data);
	char*getChar(){return Puerto;};
	unsigned getunsigned(){return Speed;};
};

