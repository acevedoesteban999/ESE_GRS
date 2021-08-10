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
 CONNECTION,SOCKET_SERVER,SOCKET_CLIENT,SERIAL_PORT
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
	static char* GetMesage(Connection*conn){return conn->message;};
};
class Socket_Client:public Connection
{
private:
	WSADATA wsData;
	SOCKET server;
	SOCKADDR_IN serveraddr,clientaddr;
	char*ip,*buffer;
	unsigned Port;
public:
	Socket_Client():Connection()
	{
		this->t=ConnectionType::SOCKET_CLIENT;
		ip=new char[1];
		buffer=new char[1024];
	}
	~Socket_Client(){
		delete[]ip;
		delete[]buffer;
		this->CloseConnection();
	};
	void CloseConnection(){
		if(EstaConectado())
		{
			closesocket(server);
			WSACleanup();
			IsConectado=false;
		}
	}
	bool inicializa(const char* Ip, unsigned long Port)
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
		this->Trasmitir("ESEGRS WIN");
		error=false;
		delete[]ip;
		this->ip=new char[strlen(Ip)+1];
	    this->ip[strlen(Ip)]=0;
	    for(unsigned i=0;i<strlen(Ip);i++)
	   	   this->ip[i]=Ip[i];
		this->Port=Port;

		return true;
	};
	char* Recibir()
	{
		if(EstaConectado())
		{
			 memset(buffer,0,sizeof(buffer));
			 int n=recv(server,buffer,255,0);
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
			 else if(n>0)
			 {
				buffer[n]=0;
				return buffer;
			 }
		}
		return NULL;
	 };
	void Trasmitir( char*buffer,SOCKET s=NULL){
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
	char*getChar(){return ip;};
	unsigned getunsigned(){return Port;};
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
	string s(string(PuertoCom)+":"+to_string(Velocidad));
	delete[]message;
	message=new char[s.length()+1];
	message[s.length()]=0;
	for(unsigned i=0;i<s.length();i++)
		message[i]=s[i];
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

