/* MILC convention gamma matrix algebra

  Adapted from MILC code for use in verifying the QLA gamma matrix
  operations.  Uses standard sign convention for gamma(YUP).
  C. DeTar 10/23/02

*/

#include <stdio.h>
#include <qla.h>

#define XUP 0
#define YUP 1
#define ZUP 2
#define TUP 3
#define SUP 4
#define SDOWN 5
#define TDOWN 6
#define ZDOWN 7
#define YDOWN 8
#define XDOWN 9

#define OPP_DIR(dir)	(9-(dir))	/* Opposite direction */

#define GAMMAFIVE -1    /* some integer which is not a direction */
#define PLUS 1          /* flags for selecting M or M_adjoint */
#define MINUS -1

/************* wp_shrink.c  ************************************/
/* 
  Compute the "Wilson projection" of a Wilson fermion vector.
  (1 +- gamma_j) is a projection operator, and we want to isolate
  the components of the vector that it keeps.  In other words, keep
  the components of the vector along the eigenvectors of 1+-gamma_j
  with eigenvalue 2, and throw away those with eigenvalue 0.

  usage:  wp_shrink( QLA_HalfFermion *dest, QLA_DiracFermion *src,
	int dir, int sign )

	If dir is one of XUP,YUP,ZUP or TUP, take the projections
	along the eigenvectors with eigenvalue +1, which survive
	multiplication by (1+gamma[dir]).
	If dir is one of XDOWN,YDOWN,ZDOWN or TDOWN, take the projections
	along the eigenvectors with eigenvalue -1, which survive
	multiplication by (1-gamma[OPP_DIR(dir)]).
	If sign=MINUS, switch the roles of +1 and -1 (ie use -gamma_dir
	instead of gamma_dir )

  Here my eigenvectors are normalized to 2, so for XYZT directions
  I won't explicitely multiply by 2.  In other words, the matrix of
  eigenvectors is sqrt(2) times a unitary matrix, and in reexpanding
  the vector I will multiply by the adjoint of this matrix.

  For UP directions, hvec.h[0] and hvec.h[2] contain the projections
  along the first and second eigenvectors respectively.
  For DOWN directions, hvec.h[0] and hvec.h[2] contain the projections
  along the third and fourth eigenvectors respectively. This results
  in down directions differing from up directions only in the sign of
  the addition.

  Note: wp_shrink( +-dir) followed by wp_grow( +-dir) amounts to multiplication
   by 1+-gamma_dir

 gamma(XUP) 			eigenvectors	eigenvalue
 	    0  0  0  i		( 1, 0, 0,-i)	+1
            0  0  i  0		( 0, 1,-i, 0)	+1
            0 -i  0  0		( 1, 0, 0,+i)	-1
           -i  0  0  0		( 0, 1,+i, 0)	-1

 gamma(YUP)			eigenvectors	eigenvalue
 	    0  0  0  1		( 1, 0, 0, 1)	+1
            0  0 -1  0		( 0, 1,-1, 0)	+1
            0 -1  0  0		( 1, 0, 0,-1)	-1
            1  0  0  0		( 0, 1, 1, 0)	-1

 gamma(ZUP)			eigenvectors	eigenvalue
 	    0  0  i  0		( 1, 0,-i, 0)	+1
            0  0  0 -i		( 0, 1, 0,+i)	+1
           -i  0  0  0		( 1, 0,+i, 0)	-1
            0  i  0  0		( 0, 1, 0,-i)	-1

 gamma(TUP)			eigenvectors	eigenvalue
 	    0  0  1  0		( 1, 0, 1, 0)	+1
            0  0  0  1		( 0, 1, 0, 1)	+1
            1  0  0  0		( 1, 0,-1, 0)	-1
            0  1  0  0		( 0, 1, 0,-1)	-1

 gamma(FIVE) 			eigenvectors	eigenvalue
 	    1  0  0  0
            0  1  0  0
            0  0 -1  0
            0  0  0 -1
*/

void wp_shrink( QLA_HalfFermion *dest, QLA_DiracFermion *src,
		int dir, int sign ){
  register int i; /*color*/
  int nc = QLA_Nc;
  
  if(sign==MINUS)dir=OPP_DIR(dir);	/* two ways to get -gamma_dir ! */
  switch(dir){
  case XUP:
    for(i=0;i<nc;i++){
      QLA_real(QLA_elem_H(*dest,i,0)) = QLA_real(QLA_elem_D(*src,i,0)) 
	- QLA_imag(QLA_elem_D(*src,i,3));
      QLA_imag(QLA_elem_H(*dest,i,0)) = QLA_imag(QLA_elem_D(*src,i,0)) 
	+ QLA_real(QLA_elem_D(*src,i,3));
      QLA_real(QLA_elem_H(*dest,i,1)) = QLA_real(QLA_elem_D(*src,i,1)) 
	- QLA_imag(QLA_elem_D(*src,i,2));
      QLA_imag(QLA_elem_H(*dest,i,1)) = QLA_imag(QLA_elem_D(*src,i,1)) 
	+ QLA_real(QLA_elem_D(*src,i,2));
    }
    break;
  case XDOWN:
    for(i=0;i<nc;i++){
      QLA_real(QLA_elem_H(*dest,i,0)) = QLA_real(QLA_elem_D(*src,i,0)) 
	+ QLA_imag(QLA_elem_D(*src,i,3));
      QLA_imag(QLA_elem_H(*dest,i,0)) = QLA_imag(QLA_elem_D(*src,i,0)) 
	- QLA_real(QLA_elem_D(*src,i,3));
      QLA_real(QLA_elem_H(*dest,i,1)) = QLA_real(QLA_elem_D(*src,i,1)) 
	+ QLA_imag(QLA_elem_D(*src,i,2));
      QLA_imag(QLA_elem_H(*dest,i,1)) = QLA_imag(QLA_elem_D(*src,i,1)) 
	- QLA_real(QLA_elem_D(*src,i,2));
    }
    break;
  case YUP:
    for(i=0;i<nc;i++){
      QLA_real(QLA_elem_H(*dest,i,0)) = QLA_real(QLA_elem_D(*src,i,0)) 
	+ QLA_real(QLA_elem_D(*src,i,3));
      QLA_imag(QLA_elem_H(*dest,i,0)) = QLA_imag(QLA_elem_D(*src,i,0)) 
	+ QLA_imag(QLA_elem_D(*src,i,3));
      QLA_real(QLA_elem_H(*dest,i,1)) = QLA_real(QLA_elem_D(*src,i,1)) 
	- QLA_real(QLA_elem_D(*src,i,2));
      QLA_imag(QLA_elem_H(*dest,i,1)) = QLA_imag(QLA_elem_D(*src,i,1)) 
	- QLA_imag(QLA_elem_D(*src,i,2));
    }
    break;
  case YDOWN:
    for(i=0;i<nc;i++){
      QLA_real(QLA_elem_H(*dest,i,0)) = QLA_real(QLA_elem_D(*src,i,0)) 
	- QLA_real(QLA_elem_D(*src,i,3));
      QLA_imag(QLA_elem_H(*dest,i,0)) = QLA_imag(QLA_elem_D(*src,i,0)) 
	- QLA_imag(QLA_elem_D(*src,i,3));
      QLA_real(QLA_elem_H(*dest,i,1)) = QLA_real(QLA_elem_D(*src,i,1)) 
	+ QLA_real(QLA_elem_D(*src,i,2));
      QLA_imag(QLA_elem_H(*dest,i,1)) = QLA_imag(QLA_elem_D(*src,i,1)) 
	+ QLA_imag(QLA_elem_D(*src,i,2));
    }
    break;
  case ZUP:
    for(i=0;i<nc;i++){
      QLA_real(QLA_elem_H(*dest,i,0)) = QLA_real(QLA_elem_D(*src,i,0)) 
	- QLA_imag(QLA_elem_D(*src,i,2));
      QLA_imag(QLA_elem_H(*dest,i,0)) = QLA_imag(QLA_elem_D(*src,i,0)) 
	+ QLA_real(QLA_elem_D(*src,i,2));
      QLA_real(QLA_elem_H(*dest,i,1)) = QLA_real(QLA_elem_D(*src,i,1)) 
	+ QLA_imag(QLA_elem_D(*src,i,3));
      QLA_imag(QLA_elem_H(*dest,i,1)) = QLA_imag(QLA_elem_D(*src,i,1)) 
	- QLA_real(QLA_elem_D(*src,i,3));
    }
    break;
  case ZDOWN:
    for(i=0;i<nc;i++){
      QLA_real(QLA_elem_H(*dest,i,0)) = QLA_real(QLA_elem_D(*src,i,0)) 
	+ QLA_imag(QLA_elem_D(*src,i,2));
      QLA_imag(QLA_elem_H(*dest,i,0)) = QLA_imag(QLA_elem_D(*src,i,0)) 
	- QLA_real(QLA_elem_D(*src,i,2));
      QLA_real(QLA_elem_H(*dest,i,1)) = QLA_real(QLA_elem_D(*src,i,1)) 
	- QLA_imag(QLA_elem_D(*src,i,3));
      QLA_imag(QLA_elem_H(*dest,i,1)) = QLA_imag(QLA_elem_D(*src,i,1)) 
	+ QLA_real(QLA_elem_D(*src,i,3));
    }
    break;
  case TUP:
    for(i=0;i<nc;i++){
      QLA_real(QLA_elem_H(*dest,i,0)) = QLA_real(QLA_elem_D(*src,i,0)) 
	+ QLA_real(QLA_elem_D(*src,i,2));
      QLA_imag(QLA_elem_H(*dest,i,0)) = QLA_imag(QLA_elem_D(*src,i,0)) 
	+ QLA_imag(QLA_elem_D(*src,i,2));
      QLA_real(QLA_elem_H(*dest,i,1)) = QLA_real(QLA_elem_D(*src,i,1)) 
	+ QLA_real(QLA_elem_D(*src,i,3));
      QLA_imag(QLA_elem_H(*dest,i,1)) = QLA_imag(QLA_elem_D(*src,i,1)) 
	+ QLA_imag(QLA_elem_D(*src,i,3));
    }
    break;
  case TDOWN:
    for(i=0;i<nc;i++){
      QLA_real(QLA_elem_H(*dest,i,0)) = QLA_real(QLA_elem_D(*src,i,0)) 
	- QLA_real(QLA_elem_D(*src,i,2));
      QLA_imag(QLA_elem_H(*dest,i,0)) = QLA_imag(QLA_elem_D(*src,i,0)) 
	- QLA_imag(QLA_elem_D(*src,i,2));
      QLA_real(QLA_elem_H(*dest,i,1)) = QLA_real(QLA_elem_D(*src,i,1)) 
	- QLA_real(QLA_elem_D(*src,i,3));
      QLA_imag(QLA_elem_H(*dest,i,1)) = QLA_imag(QLA_elem_D(*src,i,1)) 
	- QLA_imag(QLA_elem_D(*src,i,3));
    }
    break;
  case SUP:
    for(i=0;i<nc;i++){
      QLA_real(QLA_elem_H(*dest,i,0)) = QLA_real(QLA_elem_D(*src,i,0));
      QLA_imag(QLA_elem_H(*dest,i,0)) = QLA_imag(QLA_elem_D(*src,i,0));
      QLA_real(QLA_elem_H(*dest,i,1)) = QLA_real(QLA_elem_D(*src,i,1));
      QLA_imag(QLA_elem_H(*dest,i,1)) = QLA_imag(QLA_elem_D(*src,i,1));
    }
    break;
  case SDOWN:
    for(i=0;i<nc;i++){
      QLA_real(QLA_elem_H(*dest,i,0)) = QLA_real(QLA_elem_D(*src,i,2));
      QLA_imag(QLA_elem_H(*dest,i,0)) = QLA_imag(QLA_elem_D(*src,i,2));
      QLA_real(QLA_elem_H(*dest,i,1)) = QLA_real(QLA_elem_D(*src,i,3));
      QLA_imag(QLA_elem_H(*dest,i,1)) = QLA_imag(QLA_elem_D(*src,i,3));
    }
    break;
  default:
    printf("BAD CALL TO WP_SHRINK()\n");
  }
}

/***************** wp_grow.c  ************************************/
/* 
  Expand the "Wilson projection" of a Wilson fermion vector.
  (1 +- gamma_j) is a projection operator, and we are given a
  QLA_HalfFermion which contains the two components of a Wilson
  vector projected out.  This routine reexpands it to a four component
  object.

  usage:  wp_grow(  QLA_DiracFermion *dest, QLA_HalfFermion *src,
        int dir, int sign );

	If dir is one of XUP,YUP,ZUP or TUP, the projection is
	along the eigenvectors with eigenvalue +1, which survive
	multiplcation by (1+gamma[dir]).
	If dir is one of XDOWN,YDOWN,ZDOWN or TDOWN, the projection is
	along the eigenvectors with eigenvalue -1, which survive
	multiplication by (1-gamma[OPP_DIR(dir)]).
	If sign=MINUS reverse the roles of +1 and -1 - in other words
	use -gamma_dir instead of gamma_dir

  Here my eigenvectors are normalized to 2, so for XYZT directions
  I won't explicitely multiply by 2.  In other words, the matrix of
  eigenvectors is sqrt(2) times a unitary matrix, and in reexpanding
  the vector I will multiply by the adjoint of this matrix.

  For UP directions, hvec.h[0] and hvec.h[2] contain the projections
  along the first and second eigenvectors respectively.
  For DOWN directions, hvec.h[0] and hvec.h[2] contain the projections
  along the third and fourth eigenvectors respectively. This results
  in down directions differing from up directions only in the sign of
  the addition.

  Note: wp_shrink( +-dir) followed by wp_grow( +-dir) amounts to multiplication
   by 1+-gamma_dir

*/

void wp_grow(  QLA_DiracFermion *dest, QLA_HalfFermion *src,
        int dir, int sign ){
  register int i; /*color*/
  int nc = QLA_Nc;

  if(sign==MINUS)dir=OPP_DIR(dir);	/* two ways to get -gamma_dir ! */
  switch(dir){
    case XUP:
	for(i=0;i<nc;i++){
	    QLA_elem_D(*dest,i,0)      = QLA_elem_H(*src,i,0);
	    QLA_elem_D(*dest,i,1)      = QLA_elem_H(*src,i,1);
	    QLA_c_eqm_ic(QLA_elem_D(*dest,i,3), QLA_elem_H(*src,i,0));
	    QLA_c_eqm_ic(QLA_elem_D(*dest,i,2), QLA_elem_H(*src,i,1));
	}
	break;
    case XDOWN:
	for(i=0;i<nc;i++){
	    QLA_elem_D(*dest,i,0)      = QLA_elem_H(*src,i,0);
	    QLA_elem_D(*dest,i,1)      = QLA_elem_H(*src,i,1);
	    QLA_c_eq_ic(QLA_elem_D(*dest,i,3), QLA_elem_H(*src,i,0));
	    QLA_c_eq_ic(QLA_elem_D(*dest,i,2), QLA_elem_H(*src,i,1));
	}
	break;
    case YUP:
	for(i=0;i<nc;i++){
	    QLA_elem_D(*dest,i,0)      = QLA_elem_H(*src,i,0);
	    QLA_elem_D(*dest,i,1)      = QLA_elem_H(*src,i,1);
	    QLA_c_eq_c(QLA_elem_D(*dest,i,3) , QLA_elem_H(*src,i,0));
	    QLA_c_eqm_c(QLA_elem_D(*dest,i,2) ,  QLA_elem_H(*src,i,1));
	}
	break;
    case YDOWN:
	for(i=0;i<nc;i++){
	    QLA_elem_D(*dest,i,0)      = QLA_elem_H(*src,i,0);
	    QLA_elem_D(*dest,i,1)      = QLA_elem_H(*src,i,1);
	    QLA_c_eqm_c(QLA_elem_D(*dest,i,3) ,  QLA_elem_H(*src,i,0));
	    QLA_c_eq_c(QLA_elem_D(*dest,i,2) , QLA_elem_H(*src,i,1));
	}
	break;
    case ZUP:
	for(i=0;i<nc;i++){
	    QLA_elem_D(*dest,i,0)      = QLA_elem_H(*src,i,0);
	    QLA_elem_D(*dest,i,1)      = QLA_elem_H(*src,i,1);
	    QLA_c_eqm_ic(QLA_elem_D(*dest,i,2) , QLA_elem_H(*src,i,0));
	    QLA_c_eq_ic(QLA_elem_D(*dest,i,3) ,  QLA_elem_H(*src,i,1));
	}
	break;
    case ZDOWN:
	for(i=0;i<nc;i++){
	    QLA_elem_D(*dest,i,0)      = QLA_elem_H(*src,i,0);
	    QLA_elem_D(*dest,i,1)      = QLA_elem_H(*src,i,1);
	    QLA_c_eq_ic(QLA_elem_D(*dest,i,2) ,  QLA_elem_H(*src,i,0));
	    QLA_c_eqm_ic(QLA_elem_D(*dest,i,3) , QLA_elem_H(*src,i,1));
	}
	break;
    case TUP:
	for(i=0;i<nc;i++){
	    QLA_elem_D(*dest,i,0)      = QLA_elem_H(*src,i,0);
	    QLA_elem_D(*dest,i,1)      = QLA_elem_H(*src,i,1);
	    QLA_elem_D(*dest,i,2)      = QLA_elem_H(*src,i,0);
	    QLA_elem_D(*dest,i,3)      = QLA_elem_H(*src,i,1);
	}
	break;
    case TDOWN:
	for(i=0;i<nc;i++){
	    QLA_elem_D(*dest,i,0)      = QLA_elem_H(*src,i,0);
	    QLA_elem_D(*dest,i,1)      = QLA_elem_H(*src,i,1);
	    QLA_c_eqm_c(QLA_elem_D(*dest,i,2) , QLA_elem_H(*src,i,0));
	    QLA_c_eqm_c(QLA_elem_D(*dest,i,3) , QLA_elem_H(*src,i,1));
	}
	break;
    case SUP:
	for(i=0;i<nc;i++){
	    QLA_elem_D(*dest,i,0) = QLA_elem_H(*src,i,0);
	    QLA_elem_D(*dest,i,1) = QLA_elem_H(*src,i,1);
	    QLA_c_eq_r(QLA_elem_D(*dest,i,2), 0.);
	    QLA_c_eq_r(QLA_elem_D(*dest,i,3), 0.);
	}
	break;
    case SDOWN:
	for(i=0;i<nc;i++){
	    QLA_c_eq_r(QLA_elem_D(*dest,i,0), 0.);
	    QLA_c_eq_r(QLA_elem_D(*dest,i,1), 0.);
	    QLA_elem_D(*dest,i,2) = QLA_elem_H(*src,i,0);
	    QLA_elem_D(*dest,i,3) = QLA_elem_H(*src,i,1);
	}
	break;
    default:
	printf("BAD CALL TO WP_GROW()\n");
  }
}

/************* mb_gamma_l.c  ************************************/
/* 
  Multiply a Wilson matrix by a gamma matrix acting on the row index
  (This is the first index, or equivalently, multiplication on the left)
  usage: mult_by_gamma_left( QLA_DiracPropagator *dest, QLA_DiracPropagator *src,  int dir )
	dir = XUP, YUP, ZUP, TUP or GAMMAFIVE

*/

void mult_by_gamma_left(  QLA_DiracPropagator *dest, QLA_DiracPropagator *src,  int dir ){
  register int i; /*color*/
  register int c2,s2;	/* column indices, color and spin */
  int nc = QLA_Nc;
  int ns = 4;
  
  switch(dir){
  case XUP:
    for(i=0;i<nc;i++)for(s2=0;s2<ns;s2++)for(c2=0;c2<nc;c2++){
      QLA_c_eq_ic(
		  QLA_elem_P(*dest,i,0,c2,s2),
		  QLA_elem_P(*src,i,3,c2,s2));
      QLA_c_eq_ic(
		  QLA_elem_P(*dest,i,1,c2,s2),
		  QLA_elem_P(*src,i,2,c2,s2));
      QLA_c_eqm_ic(
		   QLA_elem_P(*dest,i,2,c2,s2),
		   QLA_elem_P(*src,i,1,c2,s2));
      QLA_c_eqm_ic(
		   QLA_elem_P(*dest,i,3,c2,s2),
		   QLA_elem_P(*src,i,0,c2,s2));
    }
    break;
  case YUP:
    for(i=0;i<nc;i++)for(s2=0;s2<ns;s2++)for(c2=0;c2<nc;c2++){
      QLA_c_eq_c(
		  QLA_elem_P(*dest,i,0,c2,s2),
		  QLA_elem_P(*src,i,3,c2,s2));
      QLA_c_eqm_c(
		 QLA_elem_P(*dest,i,1,c2,s2),
		 QLA_elem_P(*src,i,2,c2,s2));
      QLA_c_eqm_c(
		 QLA_elem_P(*dest,i,2,c2,s2),
		 QLA_elem_P(*src,i,1,c2,s2));
      QLA_c_eq_c(
		  QLA_elem_P(*dest,i,3,c2,s2),
		  QLA_elem_P(*src,i,0,c2,s2));
    }
    break;
  case ZUP:
    for(i=0;i<nc;i++)for(s2=0;s2<ns;s2++)for(c2=0;c2<nc;c2++){
      QLA_c_eq_ic(
		  QLA_elem_P(*dest,i,0,c2,s2),
		  QLA_elem_P(*src,i,2,c2,s2));
      QLA_c_eqm_ic(
		   QLA_elem_P(*dest,i,1,c2,s2),
		   QLA_elem_P(*src,i,3,c2,s2));
      QLA_c_eqm_ic(
		   QLA_elem_P(*dest,i,2,c2,s2),
		   QLA_elem_P(*src,i,0,c2,s2));
      QLA_c_eq_ic(
		  QLA_elem_P(*dest,i,3,c2,s2),
		  QLA_elem_P(*src,i,1,c2,s2));
    }
    break;
  case TUP:
    for(i=0;i<nc;i++)for(s2=0;s2<ns;s2++)for(c2=0;c2<nc;c2++){
      QLA_c_eq_c(
		 QLA_elem_P(*dest,i,0,c2,s2),
		 QLA_elem_P(*src,i,2,c2,s2));
      QLA_c_eq_c(
		 QLA_elem_P(*dest,i,1,c2,s2),
		 QLA_elem_P(*src,i,3,c2,s2));
      QLA_c_eq_c(
		 QLA_elem_P(*dest,i,2,c2,s2),
		 QLA_elem_P(*src,i,0,c2,s2));
      QLA_c_eq_c(
		 QLA_elem_P(*dest,i,3,c2,s2),
		 QLA_elem_P(*src,i,1,c2,s2));
    }
    break;
  case GAMMAFIVE:
    for(i=0;i<nc;i++)for(s2=0;s2<ns;s2++)for(c2=0;c2<nc;c2++){
      QLA_c_eq_c(
		 QLA_elem_P(*dest,i,0,c2,s2),
		 QLA_elem_P(*src,i,0,c2,s2));
      QLA_c_eq_c(
		 QLA_elem_P(*dest,i,1,c2,s2),
		 QLA_elem_P(*src,i,1,c2,s2));
      QLA_c_eqm_c(
		  QLA_elem_P(*dest,i,2,c2,s2),
		  QLA_elem_P(*src,i,2,c2,s2));
      QLA_c_eqm_c(
		  QLA_elem_P(*dest,i,3,c2,s2),
		  QLA_elem_P(*src,i,3,c2,s2));
    }
    break;
  default:
    printf("BAD CALL TO MULT_BY_GAMMA_LEFT()\n");
  }
}

/************* mwvb_gamma_l.c  ************************************/
/* 
  Multiply a Wilson matrix by a gamma matrix acting on the row index
  (This is the first index, or equivalently, multiplication on the left)
  usage: mult_wv_by_gamma_left( QLA_DiracFermion *dest, QLA_DiracFermion *src,  int dir )
	dir = XUP, YUP, ZUP, TUP or GAMMAFIVE

*/

void mult_wv_by_gamma_left(  QLA_DiracFermion *dest, QLA_DiracFermion *src,  int dir ){
  register int i; /*color*/
  int nc = QLA_Nc;
  
  switch(dir){
  case XUP:
    for(i=0;i<nc;i++){
      QLA_c_eq_ic(
		  QLA_elem_D(*dest,i,0),
		  QLA_elem_D(*src,i,3));
      QLA_c_eq_ic(
		  QLA_elem_D(*dest,i,1),
		  QLA_elem_D(*src,i,2));
      QLA_c_eqm_ic(
		   QLA_elem_D(*dest,i,2),
		   QLA_elem_D(*src,i,1));
      QLA_c_eqm_ic(
		   QLA_elem_D(*dest,i,3),
		   QLA_elem_D(*src,i,0));
    }
    break;
  case YUP:
    for(i=0;i<nc;i++){
      QLA_c_eq_c(
		  QLA_elem_D(*dest,i,0),
		  QLA_elem_D(*src,i,3));
      QLA_c_eqm_c(
		 QLA_elem_D(*dest,i,1),
		 QLA_elem_D(*src,i,2));
      QLA_c_eqm_c(
		 QLA_elem_D(*dest,i,2),
		 QLA_elem_D(*src,i,1));
      QLA_c_eq_c(
		  QLA_elem_D(*dest,i,3),
		  QLA_elem_D(*src,i,0));
    }
    break;
  case ZUP:
    for(i=0;i<nc;i++){
      QLA_c_eq_ic(
		  QLA_elem_D(*dest,i,0),
		  QLA_elem_D(*src,i,2));
      QLA_c_eqm_ic(
		   QLA_elem_D(*dest,i,1),
		   QLA_elem_D(*src,i,3));
      QLA_c_eqm_ic(
		   QLA_elem_D(*dest,i,2),
		   QLA_elem_D(*src,i,0));
      QLA_c_eq_ic(
		  QLA_elem_D(*dest,i,3),
		  QLA_elem_D(*src,i,1));
    }
    break;
  case TUP:
    for(i=0;i<nc;i++){
      QLA_c_eq_c(
		 QLA_elem_D(*dest,i,0),
		 QLA_elem_D(*src,i,2));
      QLA_c_eq_c(
		 QLA_elem_D(*dest,i,1),
		 QLA_elem_D(*src,i,3));
      QLA_c_eq_c(
		 QLA_elem_D(*dest,i,2),
		 QLA_elem_D(*src,i,0));
      QLA_c_eq_c(
		 QLA_elem_D(*dest,i,3),
		 QLA_elem_D(*src,i,1));
    }
    break;
  case GAMMAFIVE:
    for(i=0;i<nc;i++){
      QLA_c_eq_c(
		 QLA_elem_D(*dest,i,0),
		 QLA_elem_D(*src,i,0));
      QLA_c_eq_c(
		 QLA_elem_D(*dest,i,1),
		 QLA_elem_D(*src,i,1));
      QLA_c_eqm_c(
		  QLA_elem_D(*dest,i,2),
		  QLA_elem_D(*src,i,2));
      QLA_c_eqm_c(
		  QLA_elem_D(*dest,i,3),
		  QLA_elem_D(*src,i,3));
    }
    break;
  default:
    printf("BAD CALL TO MULT_BY_GAMMA_LEFT()\n");
  }
}

/************* mb_gamma_r.c  ************************************/
/* 
   Multiply a Wilson matrix by a gamma matrix acting on the column index
   (This is the second index, or equivalently, multiplication on the right)
   usage:   
      mult_by_gamma_right QLA_DiracPropagator *dest, QLA_DiracPropagator *src,
      int dir )
   dir = XUP, YUP, ZUP, TUP or GAMMAFIVE
*/   

void mult_by_gamma_right( QLA_DiracPropagator *dest, QLA_DiracPropagator *src, int dir ){
  register int i; /*color*/
  register int c1,s1;	/* row indices, color and spin */
  int nc = QLA_Nc;
  int ns = 4;
  
  switch(dir){
  case XUP:
    for(i=0;i<nc;i++)for(s1=0;s1<ns;s1++)for(c1=0;c1<nc;c1++){
      QLA_c_eqm_ic(
		   QLA_elem_P(*dest,c1,s1,i,0),
		   QLA_elem_P(*src,c1,s1,i,3));
      QLA_c_eqm_ic(
		   QLA_elem_P(*dest,c1,s1,i,1),
		   QLA_elem_P(*src,c1,s1,i,2));
      QLA_c_eq_ic(
		  QLA_elem_P(*dest,c1,s1,i,2),
		  QLA_elem_P(*src,c1,s1,i,1));
      QLA_c_eq_ic(
		  QLA_elem_P(*dest,c1,s1,i,3),
		  QLA_elem_P(*src,c1,s1,i,0));
    }
    break;
  case YUP:
    for(i=0;i<nc;i++)for(s1=0;s1<ns;s1++)for(c1=0;c1<nc;c1++){
      QLA_c_eq_c(
		  QLA_elem_P(*dest,c1,s1,i,0),
		  QLA_elem_P(*src,c1,s1,i,3));
      QLA_c_eqm_c(
		 QLA_elem_P(*dest,c1,s1,i,1),
		 QLA_elem_P(*src,c1,s1,i,2));
      QLA_c_eqm_c(
		 QLA_elem_P(*dest,c1,s1,i,2),
		 QLA_elem_P(*src,c1,s1,i,1));
      QLA_c_eq_c(
		  QLA_elem_P(*dest,c1,s1,i,3),
		  QLA_elem_P(*src,c1,s1,i,0));
    }
    break;
  case ZUP:
    for(i=0;i<nc;i++)for(s1=0;s1<ns;s1++)for(c1=0;c1<nc;c1++){
      QLA_c_eqm_ic(
		   QLA_elem_P(*dest,c1,s1,i,0),
		   QLA_elem_P(*src,c1,s1,i,2));
      QLA_c_eq_ic(
		  QLA_elem_P(*dest,c1,s1,i,1),
		  QLA_elem_P(*src,c1,s1,i,3));
      QLA_c_eq_ic(
		  QLA_elem_P(*dest,c1,s1,i,2),
		  QLA_elem_P(*src,c1,s1,i,0));
      QLA_c_eqm_ic(
		   QLA_elem_P(*dest,c1,s1,i,3),
		   QLA_elem_P(*src,c1,s1,i,1));
    }
    break;
  case TUP:
    for(i=0;i<nc;i++)for(s1=0;s1<ns;s1++)for(c1=0;c1<nc;c1++){
      QLA_c_eq_c(
		 QLA_elem_P(*dest,c1,s1,i,0),
		 QLA_elem_P(*src,c1,s1,i,2));
      QLA_c_eq_c(
		 QLA_elem_P(*dest,c1,s1,i,1),
		 QLA_elem_P(*src,c1,s1,i,3));
      QLA_c_eq_c(
		 QLA_elem_P(*dest,c1,s1,i,2),
		 QLA_elem_P(*src,c1,s1,i,0));
      QLA_c_eq_c(
		 QLA_elem_P(*dest,c1,s1,i,3),
		 QLA_elem_P(*src,c1,s1,i,1));
    }
    break;
  case GAMMAFIVE:
    for(i=0;i<nc;i++)for(s1=0;s1<ns;s1++)for(c1=0;c1<nc;c1++){
      QLA_c_eq_c(
		 QLA_elem_P(*dest,c1,s1,i,0),
		 QLA_elem_P(*src,c1,s1,i,0));
      QLA_c_eq_c(
		 QLA_elem_P(*dest,c1,s1,i,1),
		 QLA_elem_P(*src,c1,s1,i,1));
      QLA_c_eqm_c(
		  QLA_elem_P(*dest,c1,s1,i,2),
		  QLA_elem_P(*src,c1,s1,i,2));
      QLA_c_eqm_c(
		  QLA_elem_P(*dest,c1,s1,i,3),
		  QLA_elem_P(*src,c1,s1,i,3));
    }
    break;
  default:
    printf("BAD CALL TO MULT_BY_GAMMA_RIGHT()\n");
  }
}

