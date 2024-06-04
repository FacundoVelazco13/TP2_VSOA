/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _FILEOP_H_RPCGEN
#define _FILEOP_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct write_parameters {
	char token[32];
	char contenido[32];
};
typedef struct write_parameters write_parameters;

#define fileOp 0x1
#define version1 1

#if defined(__STDC__) || defined(__cplusplus)
#define escribir 1
extern  int * escribir_1(write_parameters *, CLIENT *);
extern  int * escribir_1_svc(write_parameters *, struct svc_req *);
extern int fileop_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define escribir 1
extern  int * escribir_1();
extern  int * escribir_1_svc();
extern int fileop_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_write_parameters (XDR *, write_parameters*);

#else /* K&R C */
extern bool_t xdr_write_parameters ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_FILEOP_H_RPCGEN */
