//
// Coreco API control declarations.
//

#ifndef _CAPICTRL_H_
#define _CAPICTRL_H_

#include <capidef.h>
#include <capimsg.h>

//
//	SAPERA messaging macros
//
#define BEGIN_MSG( msgType, msg)\
	{\
	   CORSTATUS msgStatus = CORSTATUS_IN_PROGRESS;\
	   COREVENT event;\
	   CORTRANSAC transac;\
      \
      while (CORSTATUS_ID(msgStatus) == CORSTATUS_IN_PROGRESS)\
      {\
	      if( CorManLock() == FALSE) return CORSTATUS_TIMEOUT; \
	      if ((msgStatus = CorManCreateEvent(&event)) == CORSTATUS_OK)\
	      {\
		      if ((msgStatus = CorManNewMsg (sizeof(msgType), (PCAPIMSG_MESSAGE *)&msg)) == CORSTATUS_OK)\
		      {
			      // build message here

#define BEGIN_MSG_EX( msgType, msgExtLen, msg)\
	{\
	   CORSTATUS msgStatus = CORSTATUS_IN_PROGRESS;\
	   COREVENT event;\
	   CORTRANSAC transac;\
      \
      while (CORSTATUS_ID(msgStatus) == CORSTATUS_IN_PROGRESS)\
      {\
	      if( CorManLock() == FALSE) return CORSTATUS_TIMEOUT; \
	      if ((msgStatus = CorManCreateEvent(&event)) == CORSTATUS_OK)\
	      {\
		      if ((msgStatus = CorManNewMsg (sizeof(msgType) + msgExtLen, (PCAPIMSG_MESSAGE *)&msg)) == CORSTATUS_OK)\
		      {
			      // build message here

#define SEND_MSG( msg, answer)\
			      if ((msgStatus = CorManSendMsg((PCAPIMSG_MESSAGE)msg, event, &transac)) == CORSTATUS_OK)\
			      {\
				      if ((msgStatus = CorManWaitEvent(event, CorManGetTimeout())) == CORSTATUS_OK)\
				      {\
					      if ((msgStatus = CorManGetMsg(transac, (PCAPIMSG_MESSAGE *)&answer)) == CORSTATUS_OK)\
					      {\
						      msgStatus = answer->header.cmd_status;\
						      if( msgStatus == CORSTATUS_OK)\
						      {

						      // use answer here

#define SEND_MSG_WAIT( msg, answer, timeout)\
			      if ((msgStatus = CorManSendMsg((PCAPIMSG_MESSAGE)msg, event, &transac)) == CORSTATUS_OK)\
			      {\
				      if ((msgStatus = CorManWaitEvent(event, timeout)) == CORSTATUS_OK)\
				      {\
					      if ((msgStatus = CorManGetMsg(transac, (PCAPIMSG_MESSAGE *)&answer)) == CORSTATUS_OK)\
					      {\
						      msgStatus = answer->header.cmd_status;\
						      if( msgStatus == CORSTATUS_OK)\
						      {

						      // use answer here

#define SEND_MSG_RETRY(msg, answer)\
	            if ((msgStatus = CorManSendMsg((PCAPIMSG_MESSAGE)msg, event, &transac)) == CORSTATUS_OK)\
	            {\
		            if ((msgStatus = CorManWaitEvent(event, CorManGetTimeout())) == CORSTATUS_OK)\
		            {\
			            if ((msgStatus = CorManGetMsg(transac, (PCAPIMSG_MESSAGE *)&answer)) == CORSTATUS_OK)\
			            {\
				            msgStatus = answer->header.cmd_status;\
                        if(CORSTATUS_ID(msgStatus) == CORSTATUS_RESOURCE_LOCKED)\
                        {\
                           DWORD startTime = timeGetTime();\
                           DWORD currentTime = startTime;\
                           /* Note: timeGetTime wraps around every 49.71 days */\
                           /* Note: under NT, timeGetTime default precision is 5 ms*/\
                           while( ((currentTime - startTime) < 5000) && (CORSTATUS_ID(msgStatus) == CORSTATUS_RESOURCE_LOCKED) )\
                           {\
                              CORTRANSAC localTransac;\
                              CorManUnlock();\
                              Sleep(5);\
                              if(CorManLock()==FALSE)\
                              {\
                                 msgStatus = CORSTATUS_TIMEOUT;\
                                 break;\
                              }\
                              if ((msgStatus = CorManSendMsg((PCAPIMSG_MESSAGE)msg, event, &localTransac)) == CORSTATUS_OK)\
                              {\
			                        if ((msgStatus = CorManWaitEvent(event, CorManGetTimeout())) == CORSTATUS_OK)\
			                        {\
                                    CorManFreeMsg((PCAPIMSG_MESSAGE)answer);\
				                        if ((msgStatus = CorManGetMsg(localTransac, (PCAPIMSG_MESSAGE *)&answer)) == CORSTATUS_OK)\
				                        {\
					                        msgStatus = answer->header.cmd_status;\
                                    }\
                                 }\
                              }\
                              CorManEndTransac(localTransac);\
                              currentTime = timeGetTime();\
                           } /* end of while */\
                        }\
                        if( msgStatus == CORSTATUS_OK)\
				            {

				            // use answer here

#define END_MSG_AND_TRANSAC(msg, answer)\
						      }\
						      CorManFreeMsg((PCAPIMSG_MESSAGE)answer);\
					      }\
				      }\
				      CorManEndTransac(transac);\
			      }\
			      CorManFreeMsg((PCAPIMSG_MESSAGE)msg);\
		      }\
		      CorManFreeEvent(event);\
	      }\
	      CorManUnlock(); \
	   }\
	   return msgStatus;\
	}

#define END_MSG_AND_TRANSAC_NO_RETURN(msg, answer)\
						      }\
						      CorManFreeMsg((PCAPIMSG_MESSAGE)answer);\
					      }\
				      }\
				      CorManEndTransac(transac);\
			      }\
			      CorManFreeMsg((PCAPIMSG_MESSAGE)msg);\
		      }\
		      CorManFreeEvent(event);\
	      }\
	      CorManUnlock(); \
	   }\
	}

#define END_MSG(msg, answer)\
						      }\
						      CorManFreeMsg((PCAPIMSG_MESSAGE)answer);\
					      }\
				      }\
			      }\
		      }\
	      }\
	      CorManUnlock();\
	   }\
	   return msgStatus;\
	}

#define ERROR_MSG\
	}\
	else\
	{

#define BEGIN_ANSWER( msg, answerType, answer)\
	{\
	CORSTATUS answerStatus;\
   \
	if ((answerStatus = CorManNewAnswer ((PCAPIMSG_MESSAGE)msg, sizeof(answerType), (PCAPIMSG_MESSAGE *)&answer)) == CORSTATUS_OK)\
	{
		// build answer here

#define BEGIN_ANSWER_EX( msg, answerType, answerExtLen, answer)\
	{\
	CORSTATUS answerStatus;\
   \
	if ((answerStatus = CorManNewAnswer (msg, sizeof(answerType) + answerExtLen, (PCAPIMSG_MESSAGE *)&answer)) == CORSTATUS_OK)\
	{
		// build answer here

#define SEND_ANSWER(answer)\
		answerStatus = CorManSendAnswer((PCAPIMSG_MESSAGE)answer);\
	}\
	return answerStatus;\
	}

#define UNLOCK_SAPERA_API	\
	{\
	UINT32 _nLock_= CorManUnlockThread();\

#define RELOCK_SAPERA_API   \
	CorManRelockThread( _nLock_);\
	}

//
// SAPERA global setting identifiers
//
#define CORMAN_SETTING_DATABASEKEY							"Software\\Teledyne DALSA\\Sapera LT\\Settings"

#define CORMAN_SETTING_MEM_TOPDOWN_ALLOC					0
#define CORMAN_SETTING_MEM_TOPDOWN_ALLOC_STR				"Memory Top Down Allocation"
#define CORMAN_SETTING_MEM_TOPDOWN_ALLOC_DEFAULT		0

#define CORMAN_SETTING_MSG_FIFO_SIZE						1
#define CORMAN_SETTING_MSG_FIFO_SIZE_STR					"Messaging Fifo Size"
#define CORMAN_SETTING_MSG_FIFO_SIZE_DEFAULT				128

#define CORMAN_SETTING_MSG_NUMBER_THREADS					2
#define CORMAN_SETTING_MSG_NUMBER_THREADS_STR			"Messaging Number Of Threads"
#define CORMAN_SETTING_MSG_NUMBER_THREADS_DEFAULT		4

#define CORMAN_SETTING_MSG_THREAD_PRIORITY				3
#define CORMAN_SETTING_MSG_THREAD_PRIORITY_STR			"Messaging Thread Priority"
#define CORMAN_SETTING_MSG_THREAD_PRIORITY_DEFAULT		15		// THREAD_PRIORITY_TIME_CRITICAL

#define CORMAN_SETTING_CBK_FIFO_SIZE						4
#define CORMAN_SETTING_CBK_FIFO_SIZE_STR					"Callback Fifo Size"
#define CORMAN_SETTING_CBK_FIFO_SIZE_DEFAULT				1024

#define CORMAN_SETTING_CBK_THREAD_PRIORITY				5
#define CORMAN_SETTING_CBK_THREAD_PRIORITY_STR			"Callback Thread Priority"
#define CORMAN_SETTING_CBK_THREAD_PRIORITY_DEFAULT		15		// THREAD_PRIORITY_TIME_CRITICAL

#define CORMAN_SETTING_USE_DISPLAY_SIZE               6
#define CORMAN_SETTING_USE_DISPLAY_SIZE_STR           "Use Display Size For View"
#define CORMAN_SETTING_USE_DISPLAY_SIZE_DEFAULT       1

#define CORMAN_SETTING_ENABLE_DIRECT_CALL_STR         "Enable Direct Call"

//
// SAPERA global capability identifiers
//
enum
{
   CORMAN_CAPABILITY_DEVICE_CONTEXTUAL_ERROR_REPORTING = 0,
};

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
 * CorManNewMsg
 *
 * Description:
 *		Allocate an API message.
 *
 * Parameters:
 *		nbytes	Number of bytes to allocate
 *		msg		Allocated message
 *
 *	Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManNewMsg (UINT32 nbytes, PCAPIMSG_MESSAGE *msg);

/*-----------------------------------------------------------------------------
 * CorManFreeMsg
 *
 * Description:
 *		Free an API message.
 *
 * Parameters:
 *		msg	Message to free
 *-----------------------------------------------------------------------------
 */

void CORAPIFUNC CorManFreeMsg (PCAPIMSG_MESSAGE msg);

/*-----------------------------------------------------------------------------
 * CorManNewAnswer
 *
 * Description:
 *		Allocate an API message answer.
 *
 * Parameters:
 *		msg			Message to answer
 *		nbytes		Number of bytes to allocate.
 *		answer		Allocated message 
 *
 *	Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManNewAnswer (PCAPIMSG_MESSAGE msg, UINT32 nbytes, PCAPIMSG_MESSAGE *answer);

/*-----------------------------------------------------------------------------
 * CorManSendMsg
 *
 * Description:
 *		Send a message.
 *
 * Parameters:
 *		msg			Message to send
 *		event			Event to signal (NULL = none)
 *		transac		Returned transaction handle (none if no event)
 *
 *	Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManSendMsg (PCAPIMSG_MESSAGE msg, COREVENT event, CORTRANSAC *transac);

/*-----------------------------------------------------------------------------
 * CorManSendAnswer
 *
 * Description:
 *		Send an answer message.
 *
 * Parameters:
 *		msg	Message to send
 *
 *	Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManSendAnswer (PCAPIMSG_MESSAGE msg);
typedef CORSTATUS (CCONV *CORMANSENDANSWER) (PCAPIMSG_MESSAGE msg);

/*-----------------------------------------------------------------------------
 * CorManGetServerFct
 *
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManGetServerFct( UINT32 location, UINT32 fctType, PVOID *pFct );
typedef CORSTATUS ( CCONV * CORMANGETSERVERFCT) ( UINT32 location, UINT32 fctType, PVOID *pFct  );


/*-----------------------------------------------------------------------------
 * CorManEnableDirectCall
 *
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManEnableDirectCall( BOOL32 enabled );


/*-----------------------------------------------------------------------------
 * CorManGetLocalFct
 *
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManGetLocalFct( UINT32 fctType, PVOID *pFct );
typedef CORSTATUS ( CCONV * CORMANGETLOCALFCT) ( UINT32 fctType, PVOID *pFct );

/*-----------------------------------------------------------------------------
 * CorManGetMsg
 *
 * Description:
 *		Get a message from a transaction.
 *
 * Parameters:
 *		transac		Transaction's handle
 *		msg			Returned message
 *
 *	Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManGetMsg (CORTRANSAC transac, PCAPIMSG_MESSAGE *msg);

/*-----------------------------------------------------------------------------
 * CorManEndTransac
 *
 * Description:
 *		End a transaction.
 *
 * Parameters:
 *		transac	Transaction's handle
 *-----------------------------------------------------------------------------
 */

void CORAPIFUNC CorManEndTransac (CORTRANSAC transac);

/*-----------------------------------------------------------------------------
 * CorManAppendErrorToAnswer
 *
 * Description:
 *		Reallocate answer and append last error string to the end
 *
 * Parameters:
 *		answer		Answer on which to append error string
 *		newAnswer	Reallocated answer
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManAppendErrorToAnswer (PCAPIMSG_MESSAGE answer, PCAPIMSG_MESSAGE *newAnswer);

/*-----------------------------------------------------------------------------
 * CorManCreateEvent
 *
 * Description:
 *		Create an API event.
 *
 * Parameters:
 *		apievent		Returned event handle
 *
 *	Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManCreateEvent (COREVENT *apievent);

/*-----------------------------------------------------------------------------
 * CorManFreeEvent
 *
 * Description:
 *		Free an API event.
 *
 * Parameters:
 *		apievent		Event's handle
 *-----------------------------------------------------------------------------
 */

void CORAPIFUNC CorManFreeEvent (COREVENT apievent);

/*-----------------------------------------------------------------------------
 * CorManWaitEvent
 *
 * Description:
 *		Wait an API event.
 *
 * Parameters:
 *		apievent		Event's handle
 *		timeoutms	Timeout in ms
 *
 *	Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManWaitEvent (COREVENT apievent, UINT32 timeoutms);

/*-----------------------------------------------------------------------------
 * CorManSetEvent
 *
 * Description:
 *		Signal an API event.
 *
 * Parameters:
 *		apievent		Event's handle
 *
 *	Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManSetEvent (COREVENT apievent);

/*-----------------------------------------------------------------------------
 * CorManClearEvent
 *
 * Description:
 *		Clear an API event.
 *
 * Parameters:
 *		apievent		Event's handle
 *
 *	Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManClearEvent (COREVENT apievent);

/*-----------------------------------------------------------------------------
 * CorManGetStatusText
 *
 * Description:
 *		Get text strings related to a status code (ID + Info).
 *
 * Parameters:
 *		status			Status code
 *		idBuf				ID buffer
 *		idBufSize		Size of ID buffer
 *		infoBuf			Info buffer
 *		infoBufSize		Size of info buffer
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManGetStatusText (CORSTATUS status, PSTR idBuf, UINT32 idBufSize, PSTR infoBuf, UINT32 infoBufSize);

/*-----------------------------------------------------------------------------
 * CorManGetStatusTextEx
 *
 * Description:
 *		Get the text strings related to a status code (ID + Info + Level + Module).
 *
 * Parameters:
 *		status			Status code
 *		idBuf				ID buffer
 *		idBufSize		Size of ID buffer
 *		infoBuf			Info buffer
 *		infoBufSize		Size of info buffer
 *		levelBuf			Level buffer
 *		levelBufSize	Size of level buffer
 *		moduleBuf		Module buffer
 *		moduleBufSize	Size of module buffer
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManGetStatusTextEx (CORSTATUS status, PSTR idBuf, UINT32 idBufSize, PSTR infoBuf, UINT32 infoBufSize, PSTR levelBuf, UINT32 levelBufSize, PSTR moduleBuf, UINT32 moduleBufSize);

/*-----------------------------------------------------------------------------
 * CorManGetErrorString
 *
 * Description:
 *		Get the text related to a status code.
 *
 * Parameters:
 *		status		Status code
 *		msgbuf		Message buffer
 *		msgbufsize	Message buffer size
 *
 *	Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManGetErrorString (CORSTATUS status, PSTR msgbuf, UINT32 msgbufsize);


/*-----------------------------------------------------------------------------
 * CorManGetStatusContext
 *
 * Description:
 *		Get a text string describing the context in which the last error
 *		was logged in the current thread.
 *
 * Return:
 *		Context string.
 *		last status code.
 *-----------------------------------------------------------------------------
 */
PSTR CORAPIFUNC CorManGetStatusContext (CORSTATUS *lastStatus);
typedef PSTR (CCONV * CORMANGETSTATUSCONTEXT) (CORSTATUS *lastStatus);

/*-----------------------------------------------------------------------------
 * CorManSetStatusContext
 *
 * Description:
 *		Set a text string describing the context in which the last error
 *		was logged in the current thread.
 *
 * Parameters:
 *		status	status code
 *		msg		text string
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManSetStatusContext (CORSTATUS status, PSTR msg);
typedef CORSTATUS (CCONV * CORMANSETSTATUSCONTEXT) (CORSTATUS status, PSTR msg);

/*-----------------------------------------------------------------------------
 * CorManStatusContextUpdateModule
 *
 * Description:
 *		Update the last error module.
 *
 * Parameters:
 *		saperaModule	CORSTATUS_MODULE_XXXXX
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManStatusContextUpdateModule (UINT32 saperaModule);
typedef CORSTATUS (CCONV * CORMANSTATUSCONTEXTUPDATEMODULE)(UINT32 saperaModule);

/*-----------------------------------------------------------------------------
 * CorManInstallPortServer
 *
 * Description:
 *		Install a port server.
 *
 * Parameters:
 *		porttype		Port type 
 *		callback		Message callback function. If NULL use event.
 *		msgevent		Event to signal when a message is send to the port server.
 *		
 *	Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManInstallPortServer (UINT32 porttype, PCAPIMSG_MESSAGEFUNC callback, COREVENT msgevent);
typedef CORSTATUS (CCONV *CORMANINSTALLPORTSERVER) (UINT32 porttype, PCAPIMSG_MESSAGEFUNC callback, COREVENT msgevent);

/*-----------------------------------------------------------------------------
 * CorManUninstallPortServer
 *
 * Description:
 *		Uninstall a port server.
 *
 * Parameters:
 *		porttype		Port type 
 *-----------------------------------------------------------------------------
 */

void CORAPIFUNC CorManUninstallPortServer (UINT32 porttype);
typedef void (CCONV *CORMANUNINSTALLPORTSERVER) (UINT32 porttype);


/*-----------------------------------------------------------------------------
 * CorManGetPortServerMsg
 *
 * Description:
 *  	Get a port server message.
 *
 *	Parameters:
 *		porttype		Communication port type
 *		msg			Returned message 
 *
 * Return
 *		CORSTATUS_OK if successful
 *		CORSTATUS_EMPTY if no message available
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManGetPortServerMsg (UINT32 porttype, PCAPIMSG_MESSAGE *msg);

/*-----------------------------------------------------------------------------
 * CorManNewPort
 *
 * Description:
 *  	Reserve a port on the host.
 *
 *	Parameters:
 *		portid		Port to reserve (0-253)
 *		porttype		Communication port type
 *
 * Return
 *		CORSTATUS_OK if successful.
 *		CORSTATUS_USED if the port is already used
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManNewPort (UINT8  portid, UINT32 porttype);
typedef CORSTATUS (CCONV *CORMANNEWPORT) (UINT8  portid, UINT32 porttype);

/*-----------------------------------------------------------------------------
 * CorManFreePort
 *
 * Description:
 *  	Free a port.
 *
 *	Parameters:
 *		portid	Port ID
 *-----------------------------------------------------------------------------
 */


void CORAPIFUNC CorManFreePort (UINT8  portid);
typedef void (CCONV *CORMANFREEPORT) (UINT8  portid);

/*-----------------------------------------------------------------------------
 * CorManLock
 *
 * Description:
 *  	Lock API access. Only the caller will have access to the API.
 *
 *	Return
 *		TRUE if API lock succeeded, FALSE otherwise.
 *-----------------------------------------------------------------------------
 */
BOOLEAN CORAPIFUNC CorManLock (void);
typedef BOOLEAN (CCONV *CORMANLOCK) (void);

/*-----------------------------------------------------------------------------
 * CorManUnlock
 *
 * Description:
 *  	Unlock API access.
 *-----------------------------------------------------------------------------
 */

	UINT32 CORAPIFUNC CorManUnlock (void);
	typedef UINT32 (CCONV *CORMANUNLOCK) (void);

/*-----------------------------------------------------------------------------
 * CorManGetAPILocker
 *
 * Description:
 *  	Return ID of the thread that currently have a lock on the API.

 *
 *	Return
 *		Thread ID
 *-----------------------------------------------------------------------------
 */
#if defined(POSIX_HOSTPC)
pthread_t CORAPIFUNC CorManGetAPILocker( void);
BOOLEAN CORAPIFUNC CorManIsCurrentAPILocker(void);
#else
UINT32 CORAPIFUNC CorManGetAPILocker( void);
#endif

/*-----------------------------------------------------------------------------
 * CorManReLockThread
 *
 * Description:
 *  	Lock API access. Only the caller will have access to the API.
 *
 *	Return
 *		TRUE if API lock succeeded, FALSE otherwise.
 *-----------------------------------------------------------------------------
 */
BOOLEAN CORAPIFUNC CorManRelockThread( UINT32  nCount);

/*-----------------------------------------------------------------------------
 * CorManUnlockThread
 *
 * Description:
 *  	Unlock API access.
 *-----------------------------------------------------------------------------
 */

UINT32 CORAPIFUNC CorManUnlockThread (void);

/*-----------------------------------------------------------------------------
 * CorManGetLocalServer
 *
 * Description:
 *  	Return local server handle.
 *-----------------------------------------------------------------------------
 */

CORSERVER CORAPIFUNC CorManGetLocalServer(void);
typedef CORSERVER (CCONV *CORMANGETLOCALSERVER) (void );


/*-----------------------------------------------------------------------------
 * CorManGetServer
 *
 * Description:
 *  	Return local server handle.
 *
 * Note: Obsolete. Should use CorManGetLocalServer
 *-----------------------------------------------------------------------------
 */
CORSERVER CORAPIFUNC CorManGetServer(void);


/*-----------------------------------------------------------------------------
 * CorManIsLocalHandle
 *
 * Description:
 *  	Return TRUE if handle is local
 *-----------------------------------------------------------------------------
 */

BOOLEAN CORAPIFUNC CorManIsLocalHandle( CORHANDLE handle);

/*-----------------------------------------------------------------------------
 * CorManIsLocalAddress
 *
 * Description:
 *  	Return TRUE if address is local
 *-----------------------------------------------------------------------------
 */

BOOLEAN CORAPIFUNC CorManIsLocalAddress( CAPIMSG_ADDRESS address);

// These are obsolete: use CorManIsLocalHandle
BOOLEAN CORAPIFUNC CorManIsSameHandle( CORHANDLE handle);
BOOLEAN CORAPIFUNC CorManIsSameLocation( CORHANDLE handle);

/*-----------------------------------------------------------------------------
 * CorManIsSameAddress
 *
 * Description:
 *  	Return TRUE if address is the same as local server
 *-----------------------------------------------------------------------------
 */

BOOLEAN CORAPIFUNC CorManIsSameAddress( CAPIMSG_ADDRESS address);

/*-----------------------------------------------------------------------------
 * CorManIsAcessibleLocation
 *
 * Description:
 *  	Return TRUE if handle is at an address accessible from the current server
 *-----------------------------------------------------------------------------
 */

BOOLEAN CORAPIFUNC CorManIsAccessibleLocation( CORHANDLE handle);

/*-----------------------------------------------------------------------------
 * CorManInitLocalHandle
 *
 * Description:
 *  	Return nothing
 *-----------------------------------------------------------------------------
 */
void CORAPIFUNC CorManInitLocalHandle( CORHANDLE handle, UINT32 type);


/*-----------------------------------------------------------------------------
 * CorManGetServerPort
 *
 * Description:
 *  	Get a port id for an giving server
 *
 *	Parameter:
 *		hServer		server handle
 *
 * Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManGetServerPort( CORSERVER hServer, PUINT8 port);

/*-----------------------------------------------------------------------------
 * CorManGetChildPort
 *
 * Description:
 *		Return an byte identifying the port number of child port for local server
 *
 *	Parameters:
 *	    hServer		server handle
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManGetChildPort( CORSERVER hServer, PUINT8 port);

/*-----------------------------------------------------------------------------
 * CorManGetPortAddress
 *
 * Description:
 *  	Get a port address.
 *
 *	Parameter:
 *		port		Port
 *		address	Returned address
 *
 * Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */


CORSTATUS CORAPIFUNC CorManGetPortAddress (UINT8  port, PUINT32 address);
typedef CORSTATUS (CCONV *CORMANGETPORTADDRESS) (UINT8  port, PUINT32 address);

/*-----------------------------------------------------------------------------
 * CorManGetTimeOut
 *
 * Description:
 *  	Return API timeout (ms)
 *-----------------------------------------------------------------------------
 */

UINT32 CORAPIFUNC CorManGetTimeout(void);
typedef UINT32 (CCONV *CORMANGETTIMEOUT) (void);

/*-----------------------------------------------------------------------------
 * CorManSetTimeOut
 *
 * Description:
 *  	Set API timeout (ms)
 *-----------------------------------------------------------------------------
 */

void CORAPIFUNC CorManSetTimeout(UINT32 timeoutms);

/*-----------------------------------------------------------------------------
 * CorManGetRemoteServerTCPIPAddress
 *
 * Description:
 *  	Get the TCP/IP address of a server from TCP/IP database.
 *
 *	Parameters:
 *		hServer		Remote server handle
 *		address	Returned TCP/IP address
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManGetRemoteServerTCPIPAddress(CORSERVER hServer, PUINT32 address);

/*-----------------------------------------------------------------------------
 * CorManGetServerByName
 *
 * Description:
 *		Return an handle using location name.
 *
 *	Parameters:
 *		name		Location name
 *		handle	Returned handle
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManGetServerByName( PCSTR name, PCORSERVER server);
typedef CORSTATUS (CCONV *CORMANGETSERVERBYNAME) (PCSTR name, PCORSERVER server);

/*-----------------------------------------------------------------------------
 * CorManGetServerByIndex
 *
 * Description:
 *		Return an handle using index in database
 *
 *	Parameters:
 *    index   Server Index
 *		name	  Returned location name
 *		handle  Returned handle
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManGetServerByIndex( UINT32 index, PSTR name, PCORSERVER server);
typedef CORSTATUS (CCONV *CORMANGETSERVERBYINDEX) (UINT32 index, PSTR name, PCORSERVER server);

/*-----------------------------------------------------------------------------
 * CorManGetServerBySerialNumber
 *
 * Description:
 *		Return an handle using serial number
 *
 *	Parameters:
 *    serialNumber: serial number
 *		name	        Returned location name
 *		handle	     Returned handle
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManGetServerBySerialNumber( PCSTR serialNumber, PSTR name, PCORSERVER server);

/*-----------------------------------------------------------------------------
 * CorManGetServerByType
 *
 * Description:
 *		Return an handle using board type
 *
 *	Parameters:
 *    index      server Index
 *		boardType: board type
 *    name	     Returned location name
 *		handle	  Returned handle
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManGetServerByType( UINT32 boardType, UINT32 index, PSTR name, PCORSERVER server);

/*-----------------------------------------------------------------------------
 * CorManGetServerFromHandle
 *
 * Description:
 *		Return the server handle corresponding to the specified generic handle
 *
 *	Parameters:
 *		handle: generic handle
 *		server: returned server
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManGetServerFromHandle( CORHANDLE handle, PCORSERVER server);

/*-----------------------------------------------------------------------------
 * CorManGetServerCount
 *
 * Description:
 *		Return number of server available.
 *
 *	Parameters:
 *		nServer		Returned number of server
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManGetServerCount( PUINT32 nServer);

/*-----------------------------------------------------------------------------
 * CorManGetServerParent
 *
 * Description:
 *		Return parent server handle
 *
 *	Parameters:
 *    handle	Returned parent server handle
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManGetServerParent( PCORSERVER handle);

/*-----------------------------------------------------------------------------
 * CorManGetRemoteServerParent
 *
 * Description:
 *		Return remote parent server handle
 *
 *	Parameters:
 *    handle	Returned remote parent server handle
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManGetRemoteServerParent( CORSERVER hServer, PCORSERVER handle);

/*-----------------------------------------------------------------------------
 * CorManGetServerChild
 *
 * Description:
 *		Return child server handle
 *
 *	Parameters:
 *		nChild	Child server index ( 1 .. 255)
 *    handle	Returned child server handle
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManGetServerChild( UINT8 nChild, PCORSERVER handle);

/*-----------------------------------------------------------------------------
 * CorManGetRemoteServerChild
 *
 * Description:
 *		Return remote child server handle
 *
 *	Parameters:
 *	  nChild	Remote child server index ( 1 .. 255)
 *    handle	Returned remote child server handle
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManGetRemoteServerChild( CORSERVER hServer, UINT8 nChild, PCORSERVER handle);


/*-----------------------------------------------------------------------------
 * CorManResetServer
 *
 * Description:
 *  	Reset server.
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManResetServer( CORSERVER hServer);

/*-----------------------------------------------------------------------------
 * CorManInitServer
 *
 * Description:
 *  	Initialize server.
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManInitServer( CORSERVER hServer);

/*-----------------------------------------------------------------------------
 * CorManSoftResetServer
 *
 * Description:
 *  	Reset server.
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManSoftResetServer( CORSERVER hServer);

/*-----------------------------------------------------------------------------
 * CorManGetInfo
 *
 * Description:
 *  	Return board information.
 *
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManGetServerInfo( CORSERVER hServer, void *info, UINT32 infoSize);

/*-----------------------------------------------------------------------------
 * CorManReleaseServer
 *
 * Description:
 *  	Release server handle.
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManReleaseServer( CORSERVER hServer);

/*-----------------------------------------------------------------------------
 * CorManReleaseHandle
 *
 * Description:
 *  	Release generic handle.
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManReleaseHandle( CORHANDLE handle);

/*-----------------------------------------------------------------------------
 * CorManNewFuncHandler
 *
 * Description:
 *  	Add a functions handler to the host.
 *
 * Parameters:
 *		firstcmd		First command handled
 *		lastcmd		Last command handled
 *		functable	Functions table. If NULL then signal transaction.
 *		handler		Returned handler
 *
 * Return:
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManNewFuncHandler (UINT32 firstcmd, UINT32 lastcmd, 
	PCAPIMSG_MESSAGEFUNC *functable, CORFUNCHANDLER *handler);

/*-----------------------------------------------------------------------------
 * CorManModifyFuncHandler
 *
 * Description:
 *  	Change one entry in a function handler
 *
 * Parameters:
 *		handler  Existing command handler to modify
 *		cmd      Command number to modify
 *		newfunc  New function to use for this command
 *    oldfunc  Upon return, contains the previous function handler entry
 *
 * Return:
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManModifyFuncHandler (CORFUNCHANDLER *handler, UINT32 cmd, PCAPIMSG_MESSAGEFUNC newfunc, PCAPIMSG_MESSAGEFUNC *oldfunc);

/*-----------------------------------------------------------------------------
 * CorManFreeFuncHandler
 *
 * Description:
 *  	Free a functions handler.
 *
 * Parameters:
 *		handler	Function handler
 *
 * Return:
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManFreeFuncHandler (CORFUNCHANDLER handler);

/*-----------------------------------------------------------------------------
 * CorManAllocContigBuffer
 *
 * Description:
 *  	Allocate a contiguous buffer.
 *
 *	Parameters:
 *		nbytes		Number of bytes requested
 *		pBufferphys	Returned buffer physical address
 *		ppBuffer		Returned buffer pointer
 *
 * Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManAllocContigBuffer (UINT32 nbytes, PULONG_PTR pBufferphys, PVOID *ppBuffer);

/*-----------------------------------------------------------------------------
 * CorManAllocContigBufferEx
 *
 * Description:
 *  	Allocate a contiguous buffer.
 *
 *	Parameters:
 *		nbytes		Number of bytes requested
 *		align			Requested alignment
 *		overlap		Requested 'must avoid' overlap
 *		pBufferphys	Returned buffer physical address
 *		ppBuffer		Returned buffer pointer
 *
 * Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManAllocContigBufferEx (UINT32 nbytes, UINT32 align, UINT32 overlap, PULONG_PTR pBufferphys, PVOID *ppBuffer);
typedef CORSTATUS (CCONV *CORMANALLOCCONTIGBUFFEREX) (UINT32 nbytes, UINT32 align, UINT32 overlap, PULONG_PTR pBufferphys, PVOID *ppBuffer);

/*-----------------------------------------------------------------------------
 * CorManFreeContigBuffer
 *
 * Description:
 *  	Free a contiguous buffer
 *
 *	Parameters:
 *		pBuffer	Buffer to free
 *
 * Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManFreeContigBuffer (PVOID pBuffer);
typedef CORSTATUS (CCONV *CORMANFREECONTIGBUFFER) (PVOID pBuffer);

/*-----------------------------------------------------------------------------
 * CorManLockSGBuffer
 *
 * Description:
 *    Locks a buffer in non-contiguous, page file backed, memory and returns
 *    its Scatter-Gather list the corresponding Memory Descriptor.
 *
 *	Parameters:
 *		nbytes		Number of bytes in user buffer to be locked.
 *		pUserBuffer	Pointer to user buffer to be locked.
 *    SGBufSize	Number of entries allocated for the Scatter-Gather list.
 *    pSGBuffer   Pointer to the Scatter-Gather list storage.
 *    pNumSGUsed	Returned number of entries used in Scatter-Gather list.
 *    ppMemory    Returned pointer to Memory Descriptor.
 *
 * Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManLockSGBuffer( SIZE_T nbytes, PVOID pUserBuffer, UINT32 SGBufSize, PVOID pSGBuffer, PUINT32 pNumSGUsed, PVOID *ppMemoryDesc );

/*-----------------------------------------------------------------------------
 * CorManUnlockSGBuffer
 *
 * Description:
 *    Unlocks the Scatter-Gather list for a locked buffer described by
 *    the input Memory Descriptor.
 *
 *	Parameters:
 *		pMemoryDesc	Pointer to the Memory Descriptor.
 *
 * Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManUnlockSGBuffer (PVOID pMemoryDesc);

/*-----------------------------------------------------------------------------
 * CorManUnlockAllSGBuffer
 *
 * Description:
 *    Unlocks all Scatter-Gather list for all locked buffer
 *
 *	Parameters:
 *		None.
 *
 * Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManUnlockAllSGBuffer (void);

/*-----------------------------------------------------------------------------
 * CorManMapBufferEx
 *
 * Description:
 *    Map a contiguous memory block in process space.
 *
 *	Parameters:
 *		physAddress				   : physical address
 *    	size					   : memory block size in byte
 *			pVirtualBaseAddress  : virtual base address	
 *    	ppVirtualAddress	   : returned virtual address
 *
 * Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManMapBufferEx ( ULONG_PTR physAddress, SIZE_T size, PVOID pVirtualBaseAddress, PVOID *ppVirtualAddress);

/*-----------------------------------------------------------------------------
 * CorManMapBuffer
 *
 * Description:
 *    Map a contiguous memory block in process space.
 *
 *	Parameters:
 *		physAddress   :	physical address
 *    	size          : memory block size in byte
 *    	ppVirtualAddress: returned virtual address
 *
 * Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManMapBuffer ( ULONG_PTR physAddress, SIZE_T size, PVOID *ppVirtualAddress);

/*-----------------------------------------------------------------------------
 * CorManUnmapBuffer
 *
 * Description:
 *    Unmap a contiguous memory block previously mapped by a call to CorManMapBuffer
 *
 *	Parameters:
 *		pVirtualAddress:	virtual address
 *
 * Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManUnmapBuffer ( PVOID pVirtualAddress);

/*-----------------------------------------------------------------------------
 * CorManVirtualToPhys
 *
 * Description:
 *    Return a physical address from a virtual address.
 *
 *	Parameters:
 *		   pVirtualAddress:	virtual address
 *    	pPhysAddress   : returned physical address
 *
 * Return
 *		CORSTATUS_OK if successful, error code otherwise.
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManVirtualToPhys( PVOID pVirtualAddress, PULONG_PTR pPhysAddress);

/*-----------------------------------------------------------------------------
 * CorManReadIo
 *
 * Description:
 *    Read a value from a physical port
 *
 *	Parameters:
 *		pPort     :	Address of port to read from
 *    accessType: CORMEM_IO_ACCESS_TYPE_UINT8, CORMEM_IO_ACCESS_TYPE_UINT16, CORMEM_IO_ACCESS_TYPE_UINT32
 *		pdwValue  : Address to store the read value
 *
 * Return
 *		CORSTATUS_OK if successfull
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManReadIo( PVOID pPort, UINT32 accessType, PUINT32 pdwValue);

/*-----------------------------------------------------------------------------
 * CorManWriteIo
 *
 * Description:
 *    Write a value to a physical port
 *
 *	Parameters:
 *		pPort     :	Address of port to write to
 *    accessType: CORMEM_IO_ACCESS_TYPE_UINT8, CORMEM_IO_ACCESS_TYPE_UINT16, CORMEM_IO_ACCESS_TYPE_UINT32
 *		dwValue   : Value to write
 *
 * Return
 *		CORSTATUS_OK if successfull
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManWriteIo( PVOID pPort, UINT32 accessType, UINT32 dwValue);

/*----------------------------------------------------------------
 * CorManAllocPhysMemory
 *
 * Description:
 *		Allocate physical memory
 *
 * Input:
 *		lowAddress:		specifies the physical address of the start of the first address range from which the allocated pages can come
 *		highAddress:	specifies the physical address of the end of the first address range from which the allocated pages can come
 *		skipBytes:		specifies the number of bytes to skip from the start of the previous address range from which the allocated pages can come
 *		totalBytes:		specifies the total number of bytes to allocate for the MDL
 *
 * Output:
 *		ppMDL:		         pointer to memory descriptor list
 *    totalBytesAllocated: total number of bytes allocated
 *
 *	Return value:
 *		CORSTATUS_OK if successfull
 *----------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManAllocPhysMemory( UINT64 lowAddress, UINT64 highAddress, UINT64 skipBytes, UINT64 totalBytes, PVOID *ppMDL, UINT64* totalBytesAllocated);

/*----------------------------------------------------------------
 * CorManFreePhysMemory
 *
 * Description:
 *		Free physical memory
 *
 * Input:
 *		pMDL:		pointer to memory descriptor list
 *
 * Output:
 *		None.
 *
 *	Return value:
 *		CORSTATUS_OK if successfull
 *----------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManFreePhysMemory( PVOID pMDL);

/*-----------------------------------------------------------------------------
 * CorManMapPhysMemory
 *
 * Description:
 *		Map physical memory in virtual address space
 *
 *	Input:
 *		pMDL:		pointer to memory descriptor list
 *
 * Output:
 *		ppVirtualAddr:	virtual address
 *
 * Return
 *		CORSTATUS_OK if successfull
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManMapPhysMemory( PVOID pMDL, PVOID *ppVirtualAddr);

/*-----------------------------------------------------------------------------
 * CorManUnmapPhysMemory
 *
 * Description:
 *		Unmap physical memory from virtual address space
 *
 *	Input:
 *		pMDL:		pointer to memory descriptor list
 *		pVirtualAddr: virtual address
 *
 * Return
 *		CORSTATUS_OK if successfull
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManUnmapPhysMemory( PVOID pMDL, PVOID pVirtualAddr);

/*-----------------------------------------------------------------------------
 * CorManGetPhysMemory
 *
 * Description:
 *		Get physical addresses
 *
 * Input:
 *		pMDL:				 pointer to a memory descriptor list
 *		pSGList:			 pointer to a scatter-gather list
 *		nbSGEntries:		 number of entries in the scatter-gather list
 *	
 * Output:
 *		pNbSGEntriesUsed: number of entries used in the scatter-gather list
 *
 * Return
 *		CORSTATUS_OK if successfull
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManGetPhysMemory( PVOID pMDL, PVOID pSGList, UINT32 nbSGEntries, PUINT32 pNbSGEntriesUsed);

/*-----------------------------------------------------------------------------
 * CorManGetFormatFromId
 *
 * Description:
 *		Returns the data format corresponding to the specified ID.
 *
 * Return:
 *		data format.
 *-----------------------------------------------------------------------------
 */
UINT32 CORAPIFUNC CorManGetFormatFromId(UINT32 id);

/*-----------------------------------------------------------------------------
 * CorManGetIdFromFormat
 *
 * Description:
 *		Returns the ID corresponding to the specified data format.
 *
 * Return:
 *		ID.
 *-----------------------------------------------------------------------------
 */
UINT32 CORAPIFUNC CorManGetIdFromFormat(UINT32 format);

/*-----------------------------------------------------------------------------
 * CorManGetBaseAddress
 *
 * Description:
 *		Get base address
 *
 *	Parameters:
 *    None
 *-----------------------------------------------------------------------------
 */
CAPIMSG_ADDRESS CORAPIFUNC CorManGetBaseAddress( void);

/*-----------------------------------------------------------------------------
 * CorManSetBaseAddress
 *
 * Description:
 *		Set base address
 *
 *	Parameters:
 *    address: base address
 *-----------------------------------------------------------------------------
 */
void CORAPIFUNC CorManSetBaseAddress( CAPIMSG_ADDRESS address);

/*-----------------------------------------------------------------------------
 * CorManGetAddress
 *
 * Description:
 *		Get address
 *
 *	Parameters:
 *    None
 *-----------------------------------------------------------------------------
 */
CAPIMSG_ADDRESS CORAPIFUNC CorManGetAddress( void);

/*-----------------------------------------------------------------------------
 * CorManSetBaseAddress
 *
 * Description:
 *		Set address
 *
 *	Parameters:
 *    address: address
 *-----------------------------------------------------------------------------
 */
void CORAPIFUNC CorManSetAddress( CAPIMSG_ADDRESS address);

/*-----------------------------------------------------------------------------
 * CorManGetProcessID
 *
 * Description:
 *		Get process ID
 *
 *	Parameters:
 *    None
 *-----------------------------------------------------------------------------
 */
UINT32 CORAPIFUNC CorManGetProcessID( void);
typedef UINT32 (CCONV *CORMANGETPROCESSID) (void);

/*-----------------------------------------------------------------------------
 * CorManSetProcessID
 *
 * Description:
 *		Set process ID
 *
 *	Parameters:
 *    processID: process ID
 *-----------------------------------------------------------------------------
 */
void CORAPIFUNC CorManSetProcessID( UINT32 processID);

/*-----------------------------------------------------------------------------
 * CorManSetLocalServerName
 *
 * Description:
 *		Change name of local server
 *
 *	Parameters:
 *		serverName:	server's name
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManSetLocalServerName( const char *serverName);

/*-----------------------------------------------------------------------------
 * CorManUpdateRemoteServerDatabase
 *
 * Description:
 *		Update server database on all server
 *
 *	Parameters:
 *	   None.
 * Note:
 *    Obsolete. Should use CorManUpdataAllServerDatabase.
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManUpdateRemoteServerDatabase( BOOLEAN bLocalServerDatabase);

/*-----------------------------------------------------------------------------
 * CorManUpdateAllServerDatabase
 *
 * Description:
 *		Update server database on all server
 *
 *	Parameters:
 *	   None.
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManUpdateAllServerDatabase( BOOLEAN bLocalServerDatabase);

/*-----------------------------------------------------------------------------
 * CorManUpdateServerDatabase
 *
 * Description:
 *		Update server database on a server
 *
 *	Parameters:
 *	   None.
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManUpdateServerDatabase( CORSERVER hServer, BOOLEAN bLocalServerDatabase);


/*-----------------------------------------------------------------------------
 * CorManGetNonVolatileUserData
 *
 * Description:
 *		Get user data from a non-volatile memory location of SAPERA server
 *
 *	Parameters:
 *    hServer        : server handle
 *    userDataIndex  : location index of the user data to read (in the case where the server supports multiple user data locations)
 *    userKeySize    : size of the key sent to the server to unlock the reading of the user data (in the case where the user data location needs to be unlocked to be accessed)
 *    pUserKey       : user key used to unlock access to the user data (in the case where the user data location is locked)
 *    userDataOffset : starting offset in bytes to start reading data from the user data location.
 *    userDataSize   : number of bytes to read from the user data location
 *    pUserData      : byte array to store the user data read.
 *
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManGetNonVolatileUserData(CORSERVER hServer, UINT32 userDataIndex, UINT32 userKeySize, PUINT8 pUserKey, UINT32 userDataOffset, UINT32 userDataSize, PUINT8 pUserData);


/*-----------------------------------------------------------------------------
 * CorManSetNonVolatileUserData
 *
 * Description:
 *		Set user data in a non-volatile memory location of SAPERA server
 *
 *	Parameters:
 *    hServer        : server handle
 *    userDataIndex  : location index of the user data to write (in the case where the server supports multiple user data locations)
 *    userKeySize    : size of the key sent to the server to unlock the writing of the user data (in the case where the user data location needs to be unlocked to be accessed)
 *    pUserKey       : user key used to unlock access to the user data (in the case where the user data location is locked)
 *    userDataOffset : starting offset in bytes to start writing data from the user data location.
 *    userDataSize   : number of bytes to write to the user data location
 *    pUserData      : byte array of the user data to write.
 *
 *-----------------------------------------------------------------------------
 */
 CORSTATUS CORAPIFUNC CorManSetNonVolatileUserData(CORSERVER hServer, UINT32 userDataIndex, UINT32 userKeySize, PUINT8 pUserKey, UINT32 userDataOffset, UINT32 userDataSize, PUINT8 pUserData);


/*-----------------------------------------------------------------------------
 * CorManGetServerSerialNumber
 *
 * Description:
 *		Get serial number for a SAPERA server
 *
 *	Parameters:
 *    hServer       : server handle
 *	   szSerialNumber: character array to store the serial number
 *
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManGetServerSerialNumber( CORSERVER hServer, PSTR szSerialNumber);

/*-----------------------------------------------------------------------------
 * CorManGetServerType
 *
 * Description:
 *		Get type of a SAPERA server
 *
 *	Parameters:
 *    hServer  : server handle
 *	   type     : Returned server type
 *
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManGetServerType( CORSERVER hServer, PUINT32 type);

/*-----------------------------------------------------------------------------
 * CorManGetSerial
 *
 * Description:
 *		Get serial number for all SAPERA servers
 *
 *	Parameters:
 *	   serial:	array to store serial number
 *    maxSerial: sizeof serial
 *    nSerial: pointer to store number of serial number returned
 *
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManGetSerial( UINT32 serial[], UINT32 maxSerial, PUINT32 nSerial);

/*-----------------------------------------------------------------------------
 * CorManGetSerialEx
 *
 * Description:
 *		Get serial number of any device for all SAPERA servers
 *
 *	Parameters:
 *    device:  type of device (1: Unikey, 2: Sentinel, 3: Coreco Board)
 *	   serial:	array to store serial number
 *    maxSerial: sizeof serial
 *    nSerial: pointer to store number of serial number returned
 *
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManGetSerialEx( UINT32 device, UINT32 serial[], UINT32 maxSerial, PUINT32 nSerial);

/*-----------------------------------------------------------------------------
 * CorManIsSystemHandle
 *
 * Description:
 *  	Return TRUE if handle is a system handle (PC) otherwise FALSE
 *-----------------------------------------------------------------------------
 */
BOOLEAN CORAPIFUNC CorManIsSystemHandle( CORHANDLE hHandle);

/*-----------------------------------------------------------------------------
 * CorManIsSystemAddress
 *
 * Description:
 *  	Return TRUE if address is a system address (PC) otherwise FALSE
 *-----------------------------------------------------------------------------
 */
BOOLEAN CORAPIFUNC CorManIsSystemAddress( CAPIMSG_ADDRESS);

/*-----------------------------------------------------------------------------
 * CorManIsMambaHandle
 *
 * Description:
 *  	Return TRUE if handle is a MAMBA handle otherwise FALSE
 *-----------------------------------------------------------------------------
 */
BOOLEAN CORAPIFUNC CorManIsMambaHandle( CORHANDLE hHandle);

/*-----------------------------------------------------------------------------
 * CorManIsMambaAddress
 *
 * Description:
 *  	Return TRUE if address is a MAMBA address otherwise FALSE
 *-----------------------------------------------------------------------------
 */
BOOLEAN CORAPIFUNC CorManIsMambaAddress( CAPIMSG_ADDRESS address);

/*-----------------------------------------------------------------------------
 * CorManIsBoardHandle
 *
 * Description:
 *  	Returns TRUE if handle is of the specified board type, otherwise FALSE
 *-----------------------------------------------------------------------------
 */
BOOLEAN CORAPIFUNC CorManIsBoardHandle( CORHANDLE hHandle, UINT32 boardType);

/*-----------------------------------------------------------------------------
 * CorManIsBoardAddress
 *
 * Description:
 *  	Returns TRUE if address is of the specified board type, otherwise FALSE
 *-----------------------------------------------------------------------------
 */
BOOLEAN CORAPIFUNC CorManIsBoardAddress( CAPIMSG_ADDRESS address, UINT32 boardType);

/*-----------------------------------------------------------------------------
 * CorManIsSaperaLite
 *
 * Description:
 *		Detect SAPERA Lite installation
 *
 *	Parameters:
 *    	None
 *
 * Return:
 *	   	TRUE if SAPERA Lite has been detected, FALSE otherwise
 *-----------------------------------------------------------------------------
 */
BOOLEAN CORAPIFUNC CorManIsSaperaLite( void);

/*-----------------------------------------------------------------------------
 * CorManGetInboundWindow
 *
 * Description:
 *		Get inbound window base address and size
 *
 *	Parameters:
 *    pBaseAddress: returned base address or NULL
 *    pSize       : returned size or NULL
 *
 * Return:
 *		CORSTATUS_OK
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManGetInboundWindow( PULONG_PTR pBaseAddress, PSIZE_T pSize);


/*-----------------------------------------------------------------------------
 * CorManInitInboundWindow
 *
 * Description:
 *		Initialize inbound window base address
 *
 *	Parameters:
 *    pBaseAddress: pointer to base address or NULL
 *    pSize:    pointer to size or NULL
 *-----------------------------------------------------------------------------
 */
void CORAPIFUNC CorManInitInboundWindow( PULONG_PTR pBaseAddress, PSIZE_T pSize);

/*-----------------------------------------------------------------------------
 * CorManGetOutboundWindow
 *
 * Description:
 *		Get Outbound window base address, size and translated base address
 *
 *	Parameters:
 *    pBaseAddress: pointer to base address or NULL
 *    pSize       : pointer to size or NULL
 *    pTranslatedBase: pointer to translated base or NULL
 *
 * Return:
 *		CORSTATUS_OK
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManGetOutboundWindow( PULONG_PTR pBaseAddress, PSIZE_T pSize, PULONG_PTR pTranslatedBase);

/*-----------------------------------------------------------------------------
 * CorManInitOutboundWindow
 *
 * Description:
 *		Initialized Outbound window base address
 *
 *	Parameters:
 *    pBaseAddress: pointer to base address
 *    pSize:    pointer to size
 *-----------------------------------------------------------------------------
 */
void CORAPIFUNC CorManInitOutboundWindow( PULONG_PTR pBaseAddress, PSIZE_T pSize);

/*-----------------------------------------------------------------------------
 * CorManSetOutboundWindowTranslatedBase
 *
 * Description:
 *		Set Outbound window translated base address
 *
 *	Parameters:
 *    newTranslatedBase:  translated base
 *    pOldTranslatedBase:  pointer to old translated base address
 *
 * Return
 *    CORSTATUS_OK
 *-----------------------------------------------------------------------------
 */
CORSTATUS  CORAPIFUNC CorManSetOutboundWindowTranslatedBase( ULONG_PTR newTranslatedBase, PULONG_PTR pOldTranslatedBase);


/*-----------------------------------------------------------------------------
 * CorManGetRemoteServerByName
 *
 * Description:
 *		Get server handle from a remote server by its name
 *
 *	Parameters:
 *    hRemoteServer	Returned remote server handle
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManGetRemoteServerByName( CORSERVER hServer, const char serverName[], PCORSERVER hRemoteServer);


/*-----------------------------------------------------------------------------
 * CorManExecuteCmd
 *
 * Description:
 *		Execute a command line on a server
 *
 *	Parameters:
 *    hServer:  	Server handle
 *    szCmdLine:  Command line to execute
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManExecuteCmd( CORSERVER hServer, const char szCmdLine[]);

/*-----------------------------------------------------------------------------
 * CorManRegisterHandle
 *
 * Description:
 *		Add the specified handle to the local handle database
 *
 *	Parameters:
 *    handle:  	handle to add.
 *    name:			name used to locate the handle in the database.
 *		pIndex:		pointer to return the index where the handle is stored.
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManRegisterHandle( CORHANDLE handle, PSTR name, PUINT32 pIndex);

/*-----------------------------------------------------------------------------
 * CorManUnregisterHandle
 *
 * Description:
 *		Remove the specified handle from the local database
 *
 *	Parameters:
 *    handle:  	handle to remove.
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManUnregisterHandle( CORHANDLE handle);

/*-----------------------------------------------------------------------------
 * CorManAddServerToDatabase
 *
 * Description:
 *		Add a server to SAPERA database
 *
 *	Parameters:
 *    serverName: 	server's name
 *  	location:		SAPERA address
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManAddServerToDatabase( const char serverName[], UINT32 location);
typedef CORSTATUS (CCONV *CORMANADDSERVERTODATABASE) (const char serverName[], UINT32 location);

/*-----------------------------------------------------------------------------
 * CorManSetServerServerAccessible
 *
 * Description:
 *		Mark a server as accessible/non-accessible in the SAPERA database
 *
 *	Parameters:
 *    serverName: 	server's name
 *  	location:		SAPERA address
 *    isAccessible:  new accessible state
 *
 * IMPORTANT:
 *    Starting with Sapera LT 6.20, this function is obsolete, and is replaced
 *    by the more general function CorManPnpEvent
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManSetServerAccessible( const char serverName[], UINT32 location, BOOLEAN isAccessible);
typedef CORSTATUS (CCONV *CORMANSETSERVERACCESSIBLE) (const char serverName[], UINT32 location, BOOLEAN isAccessible);

/*-----------------------------------------------------------------------------
 * CorManIsServerAccessible
 *
 *	Parameters:
 *    index   Server Index
 *
 * Description:
 *		Returns TRUE if the specified server is currently accessible
 *
 * IMPORTANT:
 *    Starting with Sapera LT 6.20, this function is obsolete, and is replaced
 *    by the more general function CorManGetServerState
 *-----------------------------------------------------------------------------
 */
BOOLEAN CORAPIFUNC CorManIsServerAccessible( UINT32 index);

/*-----------------------------------------------------------------------------
 * CorManIsMMX
 *
 * Description:
 *		Returns TRUE if local host CPU supports MMX
 *-----------------------------------------------------------------------------
 */
BOOLEAN CORAPIFUNC CorManIsMMX();

/*-----------------------------------------------------------------------------
 * CorManIsSSE
 *
 * Description:
 *		Returns TRUE if local host CPU supports SSE
 *-----------------------------------------------------------------------------
 */
BOOLEAN CORAPIFUNC CorManIsSSE();

/*-----------------------------------------------------------------------------
 * CorManIsSSE2
 *
 * Description:
 *		Returns TRUE if local host CPU supports SSE2
 *-----------------------------------------------------------------------------
 */
BOOLEAN CORAPIFUNC CorManIsSSE2();

/*-----------------------------------------------------------------------------
 * CorManIs3DNow
 *
 * Description:
 *		Returns TRUE if local host CPU supports 3D Now
 *-----------------------------------------------------------------------------
 */
BOOLEAN CORAPIFUNC CorManIs3DNow();

/*-----------------------------------------------------------------------------
 * CorManIsE3DNow
 *
 * Description:
 *		Returns TRUE if local host CPU supports extended 3D Now
 *-----------------------------------------------------------------------------
 */
BOOLEAN CORAPIFUNC CorManIsE3DNow();

/*-----------------------------------------------------------------------------
 * CorManIsHTSupported
 *
 * Description:
 *		Returns TRUE if local host CPU supports hyper thread technology
 *-----------------------------------------------------------------------------
 */
BOOLEAN CORAPIFUNC CorManIsHTSupported();

/*-----------------------------------------------------------------------------
 * CorManGetCpuBrandId
 *
 * Description:
 *		Returns the cpu brand id 
 *-----------------------------------------------------------------------------
 */
unsigned int CORAPIFUNC CorManGetCpuBrandId();

/*-----------------------------------------------------------------------------
 * CorManGetCpuCLFlushSize
 *
 * Description:
 *		Returns the cpu cache line flush size in quadword
 *-----------------------------------------------------------------------------
 */
unsigned int CORAPIFUNC CorManGetCpuCLFlushSize();

/*-----------------------------------------------------------------------------
 * CorManGetCpuApicId
 *
 * Description:
 *		Returns the cpu apic id
 *-----------------------------------------------------------------------------
 */
unsigned int CORAPIFUNC CorManGetCpuApicId();

/*-----------------------------------------------------------------------------
 * CorManGetCpuLogicalProcessors
 *
 * Description:
 *		Returns number of logical processors per physical processor
 *-----------------------------------------------------------------------------
 */
unsigned int CORAPIFUNC CorManGetCpuLogicalProcessors();

/*-----------------------------------------------------------------------------
 * CorManGetCpuType
 *
 * Description:
 *		Returns cpu type information
 *-----------------------------------------------------------------------------
 */
unsigned int CORAPIFUNC CorManGetCpuType();

/*-----------------------------------------------------------------------------
 * CorManGetCpuFamily
 *
 * Description:
 *		Returns cpu family information
 *-----------------------------------------------------------------------------
 */
unsigned int CORAPIFUNC CorManGetCpuFamily();

/*-----------------------------------------------------------------------------
 * CorManGetCpuInfo
 *
 * Description:
 *		Returns cpu information
 *-----------------------------------------------------------------------------
 */
unsigned int CORAPIFUNC CorManGetCpuInfo();

/*-----------------------------------------------------------------------------
 * CorManGetCpuVendorId
 *
 * Description:
 *		Returns cpu vendor id information
 *-----------------------------------------------------------------------------
 */
BOOLEAN CORAPIFUNC CorManGetCpuVendorId( void* vendorId, unsigned int size);

/*-----------------------------------------------------------------------------
 * CorManGetCpuVendorString
 *
 * Description:
 *		Returns cpu vendor string information
 *-----------------------------------------------------------------------------
 */
BOOLEAN CORAPIFUNC CorManGetCpuVendorString( char* szVendor, unsigned int size);

/*-----------------------------------------------------------------------------
 * CorManGetStringFromFormat
 *
 * Description:
 *		Returns TRUE on success, FALSE otherwise
 *-----------------------------------------------------------------------------
 */
BOOLEAN CORAPIFUNC CorManGetStringFromFormat( UINT32 format, char* szFormat);

/*-----------------------------------------------------------------------------
 * CorManMemcpy
 *
 * Description:
 *		Copy memory using aligned data (8 bytes alignment)
 *
 * Parameters:
 *    pDst        Pointer to first destination byte on any alignment
 *    pSrc        Pointer to first source byte on any alignment
 *    cnt         Number of bytes to copy
 *    alignSrc    Alignment on source if true; else align on destination
 *
 *	Return
 *		pDst        Pointer to first destination byte on any alignment
 *-----------------------------------------------------------------------------
 */
void * CorManMemcpy (PVOID pDst, PVOID pSrc, SIZE_T cnt, BOOLEAN alignSrc);

//
//	CorManAllocSharedBuffer
//
//	Description:
//	
//		Create a shared buffer object.
//		If the shared buffer object has already been created, this function will try to open it.
//
//		Input:
//			bufSize:	buffer size
//			szBufObjectName:	name to be given to buffer object
//			ppBufObject : internally allocated storage used to store information required 
//                     on subsequent call to CorManMapSharedBuffer, CorManFreeSharedBuffer functions.
//
//	Return TRUE on sucess, FALSE otherwise
//
BOOLEAN CORAPIFUNC CorManAllocSharedBuffer( UINT64 bufSize, const char *szBufObjectName, void **ppBufObject);

//
//	CorManOpenSharedBuffer
//
//	Description:
//	
//		Open a shared buffer object that has already been allocated by a call to CorManAllocSharedBuffer.
//
//		Input:
//			szBufObjectName:	name of a buffer object that has already been allocated
//			ppBufObject : internally allocated storage used to store information required 
//                     on subsequent call to CorManMapSharedBuffer, CorManFreeSharedBuffer functions.
//
//	Return TRUE on sucess, FALSE otherwise
//
BOOLEAN CORAPIFUNC CorManOpenSharedBuffer(const char *szBufObjectName, void** ppBufObject);

//
//	CorManFreeSharedBuffer
//
//	Description:
//	
//		Free a shared buffer object
//
//		Input:
//			pBufObject: buffer object as returned by a call to either CorManAllocShreadBuffer or CorManOpenSharedBuffer functions
//
//	Return TRUE on sucess, FALSE otherwise
//
BOOLEAN CORAPIFUNC CorManFreeSharedBuffer( void* pBufObject);

//
//	CorManMapSharedBuffer
//
//	Description:
//	
//		Map a view on a shared buffer object
//
//		Input:
//			pBufObject: buffer object as returned by call to either CorManAllocShareBuffer or CorManOpenSharedBuffer functions.
//			bufOffset : offset from the beginning of the buffer
//			bufMapSize: number of bytes to map
//
//	Return the virtual address that pointed to the first buffer on success, NULL otherwise
//
CORAPIEXPORT void * CCONV CorManMapSharedBuffer( void *pBufObject, UINT64 bufOffset, UINT64 bufMapSize, void **ppBufMapObject);

//
//	CorManUnmapSharedBuffer
//
//	Description:
//	
//		Unmap a view of a shared buffer object
//
//		Input:
//			pBufMapObject: information as returned by a call to CorManMapSharedBuffer function
//
//	Return TRUE on sucess, FALSE otherwise
//
BOOLEAN CORAPIFUNC CorManUnmapSharedBuffer( void *pBufMapObject);

//
//	CorManHasCreatedSharedBuffer
//
//	Description:
//	
//		Check if the shared buffer has been created by the current process
//
//		Input:
//			pBufMapObject: information as returned by a call to CrcMapSharedBuffer function
//
//	Return TRUE if the current process has created the shared buffer, FALSE otherwise
//
BOOLEAN CORAPIFUNC CorManHasCreatedSharedBuffer( void *pBufObject);

//
//	CorManLockSharedBuffer
//
//	Description:
//	
//		Allow to lock access to share buffer
//		Any process willing to access a shared buffer should call this function prior accessing it
//
//		Input:
//			pBufMapObject: information as returned by a call to CrcMapSharedBuffer function
//			timeOut:       maximum waiting time in milliseconds ( -1 == INFINITE)
//
//	Return TRUE if the current process can access safely the shared buffer, FALSE otherwise
//
BOOLEAN CORAPIFUNC CorManLockSharedBuffer( PVOID pBufObject, UINT32 timeOut);

//
//	CorManUnlockSharedBuffer
//
//	Description:
//	
//		Release access to a shared buffer
//
//		Input:
//			pBufMapObject: information as returned by a call to CrcMapSharedBuffer function
//
//	Return TRUE on success, FALSE otherwise
//
BOOLEAN CORAPIFUNC CorManUnlockSharedBuffer( void *pBufObject);

//
//	CorManAllocUserBuffer
//
//	Description:
//
//		Allocate user buffers 
//
//		Input:
//			bufSize		: buffer size
//
//	   Output:
//			bufSize	   : buffer size that has been allocated ( can be least than what have been requested)
//			ppBufObject : internally allocated storage used to store information required 
//                     on subsequent call to CorManMapUserBuffer, CorManFreeUserBuffer functions.
//
//		Return TRUE on success, FALSE otherwise
//
//	NOTE:
//
//		(1) Memory allocated by this function must be physically present in the system.
//		(2) After the memory has been allocated, it is locked down and unavailable to the rest of the virtual memory management system.
//		(3) Physical pages allocated through this function cannot be simultaneously mapped at more than one virtual address.
//		(4) Physical pages can reside at any physical address. You should make no assumptions about the contiguity of the physical pages.
//
BOOLEAN CORAPIFUNC CorManAllocUserBuffer( UINT64* bufSize, void** ppBufObject);

//
//	CorManFreeUserBuffer
//
//	Description:
//
//		Free user buffers
//
//		Input:
//			pBufObject: buffer object as returned by a call to CorManAllocUserBuffer function
//
//	Return TRUE on success, FALSE otherwise
//
//
//
BOOLEAN CORAPIFUNC CorManFreeUserBuffer( void* pBufObject);

//
//	CorManMapUserBufferEx
//
//	Description:
//
//		Map a user buffer into virtual address space
//
//		Input:
//			pBufObject: buffer object as returned by call to CorManAllocUserBuffer function
//			bufOffset : offset from the beginning of the buffer
//			bufMapSize: number of bytes to map
//			virtualAddress: virtual address at which the buffer will be mapped
//
//		Output:
//			pBufMapObject: used to store information required when calling CorManUnmapUserBuffer function.
//
//	Return the virtual address that pointed to the first buffer on success, NULL otherwise
//
// NOTE:
//
// (1) This function maps previously allocated physical memory pages within an Address Windowing Extensions (AWE) region.
// (2) You can map multiple regions simultaneously, provided they do not overlap.
//
//
CORAPIEXPORT void* CCONV CorManMapUserBufferEx( void* pBufObject, UINT64 bufOffset, UINT64 bufMapSize, void* virtualAddress, void **ppBufMapObject);

//
//	CorManMapUserBuffer
//
//	Description:
//
//		Map a user buffer into virtual address space
//
//		Input:
//			pBufObject: buffer object as returned by call to CorManAllocUserBuffer function
//			bufOffset : offset from the beginning of the buffer
//			bufMapSize: number of bytes to map
//
//		Output:
//			pBufMapObject: used to store information required when calling CorManUnmapUserBuffer function.
//
//	Return the virtual address that pointed to the first buffer on success, NULL otherwise
//
// NOTE:
//
// (1) This function maps previously allocated physical memory pages within an Address Windowing Extensions (AWE) region.
// (2) You can map multiple regions simultaneously, provided they do not overlap.
//
//
CORAPIEXPORT void* CCONV CorManMapUserBuffer( void* pBufObject, UINT64 bufOffset, UINT64 bufMapSize, void **ppBufMapObject);

//
//	CorManUnmapUserBuffer
//
//	Description:
//
//		Unmap a user buffer from virtual address space
//
//		Input:
//			pBufMapObject: information as returned by a call to CorManMapUserBuffer function
//
//	Return TRUE on sucess, FALSE otherwise
//
//	NOTE:
//		(1) The physical pages may be unmapped but they are not freed. 
//			 You must call FreeBuffers to free the physical pages.
//
BOOLEAN CORAPIFUNC CorManUnmapUserBuffer( void* pBufMapObject);

/*-----------------------------------------------------------------------------
 * CorManWaitForServerReady
 *
 * Description:
 *		Wait until
 *
 * Parameters:
 *    hBoard      Handle to the server
 *    timeout     Maximum time (in milliseconds) to wait before returning an error
 *
 *-----------------------------------------------------------------------------
 */

CORSTATUS CORAPIFUNC CorManWaitForServerReady(CORSERVER hBoard, UINT32 timeout);

/*-----------------------------------------------------------------------------
 * CorManGetPixelDepthMin
 *
 * Description:
 *		Returns the minimum number of bits per plane for the specified data format.
 *
 * Return:
 *		Number of bits.
 *-----------------------------------------------------------------------------
 */
UINT32 CORAPIFUNC CorManGetPixelDepthMin(UINT32 format);

/*-----------------------------------------------------------------------------
 * CorManGetPixelDepthMax
 *
 * Description:
 *		Returns the maximum number of bits per plane for the specified data format.
 *
 * Return:
 *		Number of bits.
 *-----------------------------------------------------------------------------
 */
UINT32 CORAPIFUNC CorManGetPixelDepthMax(UINT32 format);

/*-----------------------------------------------------------------------------
 * CorManGetSetting
 *
 * Description:
 *		Returns the current value of a SAPERA setting
 *
 * Parameters:
 *		id:			setting identifier
 *		pValue:		storage for setting
 *		size:			size of storage
 *
 * Return:
 *		CORSTATUS_OK on success
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManGetSetting( UINT32 id, void *pValue, UINT32 size);
typedef CORSTATUS (CCONV *CORMANGETSETTING) ( UINT32 id, void *pValue, UINT32 size);

/*-----------------------------------------------------------------------------
 * CorManSetSetting
 *
 * Description:
 *		Sets the current value for a SAPERA setting
 *
 * Parameters:
 *		id:			setting identifier
 *		pValue:		storage for setting
 *		size:			size of storage
 *
 * Return:
 *		CORSTATUS_OK on success
 *-----------------------------------------------------------------------------
 */
CORSTATUS CORAPIFUNC CorManSetSetting( UINT32 id, void *pValue, UINT32 size);

/*-----------------------------------------------------------------------------
* CorManGetCapability
*
* Description:
*		Get the current value for a SAPERA capability
*
* Parameters:
*		id:			  capability identifier
*		pCapability:  storage for capability
*
* Return:
*		CORSTATUS_OK on success
*-----------------------------------------------------------------------------
*/
CORSTATUS CORAPIFUNC CorManGetCapability(UINT32 id, UINT32 *pCapability);
typedef CORSTATUS(CCONV *CORMANGETCAPABILITY) (UINT32 id, UINT32 *pCapability);

/*----------------------------------------------------------------
CorMemLoad

Description:
	Load CorApi.dll and initialize is functions table
	(Only need if for static loading of CorApi)

Input:
	
Output:

Return value:
	TRUE if successfull, FALSE otherwise
----------------------------------------------------------------*/
#ifndef _CORAPI_LOAD_MANUAL_
	#define CorApiLoad(moduleName) TRUE
#else
	BOOLEAN CorApiLoad(const char *moduleName);
#endif // _CORAPI_LOAD_MANUAL_

/*----------------------------------------------------------------
CorApiGetFunctions

Description:
	initialize the CorApi.dll functions table
	(Only need if for static loading of CorApi)

Input:
	
Output:

Return value:
	TRUE if successfull, FALSE otherwise
----------------------------------------------------------------*/
#ifndef _CORAPI_LOAD_MANUAL_
	#define CorApiGetFunctions(moduleName) TRUE
#else
	BOOLEAN CorApiGetFunctions(const char *moduleName);
#endif // _CORAPI_LOAD_MANUAL_

	/*----------------------------------------------------------------
CorMemUnLoad

Description:
	Unload CorApi.dll and clear is functions table
	(Only need if for static loading of CorApi)

Input:
	
Output:

Return value:
	TRUE if successfull, FALSE otherwise
----------------------------------------------------------------*/
#ifndef _CORAPI_LOAD_MANUAL_
	#define CorApiUnload() 
#else
	void  CorApiUnload(void);
#endif // _CORAPI_LOAD_MANUAL_

// Macros with variable argument list not supported before Visual Studio 2005
// In Linux they are supported with a slightly different syntax.
#if (defined(_MSC_VER) &&  _MSC_VER >= 1400) || defined(POSIX_HOSTPC)
#define DIRECT_CALL_START( _fctType, _server, ... )\
   {\
	   _fctType##_FCT fct; \
      __VA_ARGS__\
	   if( CorManGetServerFct( CORHANDLE_LOCATION( _server), _fctType,  (PVOID *) &fct )  == CORSTATUS_OK) \
      { \
		   CORSTATUS fctStatus = CORSTATUS_IN_PROGRESS;\
         while( CORSTATUS_ID(fctStatus) == CORSTATUS_IN_PROGRESS )\
         {

#define DIRECT_CALL_SUCCESS()\
         }\
         if( !fctStatus) {

// Error managemet use cases:
//  DC retutns CORSTATUS_OK: Do not chang the status context.
//  DC retutns an error status and the CorManGetStatusContext is CORSTATUS_OK: Set the error code
//  DC retutns an error status and the CorManGetStatusContext is a different error status : This is an old error overewrite error.
//  DC retutns an error status and the CorManGetStatusContext is the same error status : The staus context was probably set by the server do not touch.

#define DIRECT_CALL_ERROR()\
         }\
         if(fctStatus) {\
            CORSTATUS _status = CORSTATUS_OK;\
            CorManGetStatusContext( &_status);\
            if(_status != fctStatus)\
            {\
               CorManSetStatusContext( fctStatus,"");\
            }
            

#define DIRECT_CALL_END()\
         }\
		   return fctStatus;\
      }\
   }


#if defined(POSIX_HOSTPC)
// Variadic macro definitions for gcc (hopefully version independent)
// are slightly different than for Windows
#define DIRECT_CALL( _fctType, _server, ... )\
   DIRECT_CALL_START(_fctType, _server)\
      if(CORHANDLE_LOCAL_ADDRESS(_server))\
         fctStatus = fct( CORHANDLE_LOCAL_ADDRESS(_server), ## __VA_ARGS__);\
      else\
         fctStatus = fct( _server, ## __VA_ARGS__);\
   DIRECT_CALL_ERROR()\
   DIRECT_CALL_END()


#define DIRECT_CALL_AND_FREE_HANDLE( _fctType, _server, ...)\
   DIRECT_CALL_START(_fctType, _server)\
      if(CORHANDLE_LOCAL_ADDRESS(_server))\
         fctStatus = fct( CORHANDLE_LOCAL_ADDRESS(_server), ## __VA_ARGS__);\
      else\
         fctStatus = fct( _server, ## __VA_ARGS__);\
   DIRECT_CALL_SUCCESS()\
      CORHANDLE_FREE(  _server);\
   DIRECT_CALL_ERROR()\
   DIRECT_CALL_END()


#else  // POSIX_HOSTPC (above)

#define DIRECT_CALL( _fctType, _server, ... )\
   DIRECT_CALL_START(_fctType, _server)\
      if(CORHANDLE_LOCAL_ADDRESS(_server))\
         fctStatus = fct( CORHANDLE_LOCAL_ADDRESS(_server), __VA_ARGS__);\
      else\
         fctStatus = fct( _server, __VA_ARGS__);\
   DIRECT_CALL_ERROR()\
   DIRECT_CALL_END()


#define DIRECT_CALL_AND_FREE_HANDLE( _fctType, _server, ...)\
   DIRECT_CALL_START(_fctType, _server)\
      if(CORHANDLE_LOCAL_ADDRESS(_server))\
         fctStatus = fct( CORHANDLE_LOCAL_ADDRESS(_server), __VA_ARGS__);\
      else\
         fctStatus = fct( _server, __VA_ARGS__);\
   DIRECT_CALL_SUCCESS()\
      CORHANDLE_FREE(  _server);\
   DIRECT_CALL_ERROR()\
   DIRECT_CALL_END()


#endif // _MSV_VER >= 1400 

#define DIRECT_CALL_NEW( _fctType, _server, _handle, ...)\
   DIRECT_CALL_START(_fctType, _server, CORHANDLE handle= CORHANDLE_NULL;)\
      fctStatus = fct(  __VA_ARGS__ ); \
   DIRECT_CALL_SUCCESS()\
      CORHANDLE_COPY( *_handle, handle);\
      CORHANDLE_LOCATION( *_handle)= CORHANDLE_LOCATION( _server);\
   DIRECT_CALL_ERROR()\
      CORHANDLE_FREE( * _handle);\
   DIRECT_CALL_END()

#define DIRECT_CALL_NEW_EX( _fctType, _server, _handle, ...)\
   DIRECT_CALL_START(_fctType, _server)\
            fctStatus = fct(  __VA_ARGS__ ); \
   DIRECT_CALL_ERROR()\
      CORHANDLE_FREE( * _handle);\
   DIRECT_CALL_END()

#define DIRECT_CALL_NEW_EX_EX( _fctType, _server, _handle1, _handle2, ...)\
   DIRECT_CALL_START(_fctType, _server, CORHANDLE handle= CORHANDLE_NULL;)\
            fctStatus = fct(  __VA_ARGS__ ); \
   DIRECT_CALL_SUCCESS()\
      CORHANDLE_COPY( *_handle1, handle);\
      CORHANDLE_LOCATION( *_handle1)= CORHANDLE_LOCATION( _server);\
   DIRECT_CALL_ERROR()\
      CORHANDLE_FREE( * _handle1);\
      CORHANDLE_FREE( * _handle2);\
   DIRECT_CALL_END()

#endif // _MSC_VER >= 1400 or POSIX_HOSTPC

#ifdef __cplusplus
}
#endif

#endif   // _CAPICTRL_H_
