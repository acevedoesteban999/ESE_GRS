#pragma once
#include <iostream>
#include <winsock.h>
#include <windows.h>
#include <string>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
enum ConnectionType
{
 CONNECTION,TCP_IP_SERVER,TCP_IP_CLIENT,SERIAL_PORT
};
class Connection
{
protected:
	ConnectionType t;
	WSADATA wsData;
	SOCKET server,cliente;
	SOCKADDR_IN serveraddr,clientaddr;
	bool IsConectado;
	bool error;
	char*errorstr,*ip,*message; 
	char buffer[1024];
	unsigned Port;
public:
	Connection(){
		t=ConnectionType::CONNECTION;
		IsConectado=error=false;
		errorstr=new char(0);
		ip=new char(0);
		message=new char(0);
		Port=0;
	};
	virtual ~Connection(){};
	virtual void CloseConnection(){};
	virtual bool inicializa(const char*Ip, unsigned long Port){return false;};
	virtual char* Recibir()
	{
		if(EstaConectado())
		{
			 memset(buffer,0,sizeof(buffer));
			 int n=recv(t==ConnectionType::TCP_IP_SERVER?cliente:server,buffer,sizeof(buffer),0);
			 if(n==0)
			 {
				 errorstr="Error 0 ";
				 error=true;
				 return NULL;
			 }
			 if(n==-1)
			 {
					errorstr="Error 1 ";
					error=true;
					return NULL;
			 }
			 return buffer;
		}
		return NULL;
	 };
	virtual void Trasmitir( char*buffer){
		int n=send(t==ConnectionType::TCP_IP_SERVER?cliente:server,buffer,sizeof(buffer)+(strlen(buffer)>4?strlen(buffer)-4:0),0);
		 if(n==0)
		 {
		  errorstr="Error 0 ";
		  error=true;
		  return;
		 }
		  if(n==-1)
		 {
			errorstr="Error 1 ";
		    error=true;
			return;
		 }
	 };
	bool Error(){return error;};
	bool EstaConectado(){return IsConectado;};
	char* ErrorStr(){return errorstr;};
	virtual char*getChar(){return new char(0);};
	virtual unsigned getunsigned(){return 0;};
	virtual char* ActionAfterError(){return new char(0);};
	ConnectionType GetType(){return t;};
	static void SetType(ConnectionType CT,Connection*conn){conn->t=CT;};
	static char* GetMesage(Connection*conn){return conn->message;};
};
class TcP_ip_Server:public Connection
{
public:
	TcP_ip_Server():Connection()
	{
		this->t=ConnectionType::TCP_IP_SERVER;
	}
	~TcP_ip_Server()
	{
	   if(this->EstaConectado())
	   {
		   this->CerrarSocket();
	   }
	};
	void CloseConnection(){
		CerrarSocket();
	}
	void CerrarSocket()
	{
		closesocket(cliente);
		WSACleanup();
		IsConectado=false;
	} 
	bool inicializa(const char* Ip, unsigned long Port)
	 {
		WSAStartup(MAKEWORD(2,0),&wsData);
		if((server=socket(AF_INET,SOCK_STREAM,0))<0)
		{
			this->error=true;
			this->errorstr="Error 1";
			CerrarSocket();
			return false;
		}
		serveraddr.sin_addr.s_addr=inet_addr((const char*)Ip);   //INADDR_ANY;
		serveraddr.sin_family=AF_INET;
		serveraddr.sin_port=htons((u_short)Port);
		if(::bind(server,(SOCKADDR*)&serveraddr,sizeof(serveraddr))!=0)
		{
			this->error=true;
			this->errorstr="Error 2";
			CerrarSocket();
			return false;
	   }
		if(listen(server,0)!=0)
		{
			this->error=true;
			this->errorstr="Error 3";
			CerrarSocket();
			return false;
		}

		error=false;
		IsConectado=true;
		this->ip=new char[strlen(Ip)+1];
	    this->ip[strlen(Ip)]=0;
	    for(unsigned i=0;i<strlen(Ip);i++)
	   	   this->ip[i]=Ip[i];
		this->Port=Port;
		return true;
	 
	 }
	char*getChar(){return ip;};
	unsigned getunsigned(){return Port;};
	char* ActionAfterError()
	{
		if(error=true)
		{
		   return ConnectClient();
		}
		return "No habia un error";
	};
	char* ConnectClient()
	{
		int clientaddrSize=sizeof(clientaddr);
		   if((cliente=accept(server,(SOCKADDR*)&clientaddr,&clientaddrSize))<0)
		   {
			  this->error=true;
			  this->errorstr="Error al conectar un cliente";
			  return this->errorstr;
		   }
		   this->message="Cliente Conectado";
		   error=false;
		   return this->message;
	}
};
class TcP_ip_Client:public Connection
{
public:
	TcP_ip_Client():Connection()
	{
		this->t=ConnectionType::TCP_IP_CLIENT;
	}
	~TcP_ip_Client(){
	if(this->EstaConectado())
			this->CerrarSocket();
	};
	void CloseConnection(){
		CerrarSocket();
	}
	void Send()
	{
		cin>>this->buffer;
		cout<<endl;
		send(server,buffer,sizeof(buffer),0);
		memset(buffer,0,sizeof(buffer));
	}
	void CerrarSocket()
	{
		closesocket(server);
		WSACleanup();
		IsConectado=false;	
	}
	bool inicializa(const char* Ip, unsigned long Port)
	{
	    WSAStartup(MAKEWORD(2,0),&wsData);
		if((server=socket(AF_INET,SOCK_STREAM,0))<0)
		{
			this->error=true;
			this->errorstr="Error 0 ";
			CerrarSocket();
			return false;
		}
		serveraddr.sin_addr.s_addr=inet_addr((const char*)Ip);
		serveraddr.sin_family=AF_INET;
		serveraddr.sin_port=htons((u_short)Port);
		if(connect(server,(SOCKADDR*)&serveraddr,sizeof(serveraddr))<0)
		 {
			string*s=new string("C_Error 1 :"+string(Ip)+":"+to_string(Port));
			this->error=true;
			this->errorstr=(char*)s->c_str();
			CerrarSocket();
			return false;
		 }
		else
		{
		string*s=new string(string(Ip)+":"+to_string(Port));
		this->message=(char*)s->c_str();
		}


		error=false;
		IsConectado=true;
		this->ip=new char[strlen(Ip)+1];
	    this->ip[strlen(Ip)]=0;
	    for(unsigned i=0;i<strlen(Ip);i++)
	   	   this->ip[i]=Ip[i];
		this->Port=Port;

		return true;
	};
	char*getChar(){return ip;};
	unsigned getunsigned(){return Port;};
	char* ActionAfterError()
	{
	  if(error=true)
		{
			if(inicializa(this->ip,this->Port))
				return this->message;
			else
				return this->errorstr;
	    }
	  return "NULL";
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
		Puerto=new char(0);
		this->t=ConnectionType::SERIAL_PORT;
	};
	//PuertoSerie(System::String^PuertoCom, unsigned long Velocidad);
	~PuertoSerie()
    {
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
		string*s=new string("C_Error 0 :"+string(PuertoCom)+":"+to_string(Velocidad));
		error=true;
		errorstr=(char*)s->c_str();
		return false;
	}
	DCB ParametrosTxSerie;
	if (!GetCommState(handler,&ParametrosTxSerie))
	{
		string*s=new string("Error 1 :"+string(PuertoCom)+":"+to_string(Velocidad));
		error=true;
		errorstr=(char*)s->c_str();
		return false;
	}
	ParametrosTxSerie.DCBlength=sizeof(DCB);
	ParametrosTxSerie.BaudRate=Velocidad;
	ParametrosTxSerie.ByteSize=8;
	ParametrosTxSerie.StopBits=TWOSTOPBITS;
	ParametrosTxSerie.Parity=(BYTE)PARITY_NONE;
	if(!SetCommState(handler,&ParametrosTxSerie))
	{
		string*s=new string("Error 2 :"+string(PuertoCom)+":"+to_string(Velocidad));
		error=true;
		errorstr=(char*)s->c_str();
		return false;
	}
	IsConectado=true;
	PurgeComm(handler,PURGE_RXCLEAR|PURGE_TXCLEAR);
	error=false;
	this->Puerto=new char[strlen(PuertoCom)+1];
	this->Puerto[strlen(PuertoCom)]=0;
	for(unsigned i=0;i<strlen(PuertoCom);i++)
		this->Puerto[i]=PuertoCom[i];
	this->Speed=Velocidad;
	string*s=new string(string(PuertoCom)+":"+to_string(Velocidad));
	this->message=(char*)s->c_str();
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
			this->errorstr="Error 0 ";
			return NULL;
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
	void Trasmitir(char *oBuffer)
{
	DWORD iBytesWritten;
	iBytesWritten=0;
	WriteFile(handler,oBuffer,strlen(oBuffer),&iBytesWritten,NULL);
}
	//void Trasmitir(System::String^data);
	bool Error(){return error;};
	char* ErrorStr(){return errorstr;};
	char*getChar(){return Puerto;};
	unsigned getunsigned(){return Speed;};
};

