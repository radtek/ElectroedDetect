//
// Messages API definitions.
//

#ifndef _CAPIMSG_H_
#define _CAPIMSG_H_

#include <corenv.h>
#include <capidef.h>
#include <corlib.h>

#define CAPIMSG_TRANSAC_FIFOSIZE			128
#define CAPIMSG_MSGCONTROL_ANSWER			1	/* set if message is an answer */
#define CAPIMSG_MSGCONTROL_PORTCTRL			2	/* set if the message is addressed to the port */
#define CAPIMSG_MSGCONTROL_NOTRANSACTION	4	/* set if no transaction requested */	

typedef UINT32 CAPIMSG_ADDRESS, *PCAPIMSG_ADDRESS;	

#include "cpackd.h"

typedef struct COR_PACK {	//(EC)STRUCT
	UINT32	        msglen;
	UINT32	        transac;
	UINT32	        control;
	CAPIMSG_ADDRESS  from;
	CAPIMSG_ADDRESS  to;
	UINT32	        port;
	UINT32	        rport;
	UINT32	        cmd_status;		// command and status
	UINT32			  errorOffset;		// Non-zero if error is appended
	/* data ... */
} CAPIMSG_MESSAGE, *PCAPIMSG_MESSAGE;

typedef CORSTATUS (*PCAPIMSG_MESSAGEFUNC)(PCAPIMSG_MESSAGE msg);

typedef struct COR_PACK { //(EC)STRUCT
	UINT32		         active;
	UINT32		         id;
	CORKEVENT	         event;
	UINT32		         fifohead;
	UINT32		         fifotail;
	UINT32		         processid;
	PCAPIMSG_MESSAGE     fifo[CAPIMSG_TRANSAC_FIFOSIZE];
	PCAPIMSG_MESSAGEFUNC callback;
} CAPIMSG_TRANSAC, *PCAPIMSG_TRANSAC;
												
#include "cunpackd.h"

#endif   // _CAPIMSG_H_
