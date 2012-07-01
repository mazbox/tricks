//
//  Ellipser.cpp
//  opencvExample
//
//  Created by Marek Bereza on 14/07/2011.
//  Copyright 2011 MAZBOX LTD. All rights reserved.
//

#include "Ellipse.h"
#include "geomutils.h"

#define NPTS 100
using namespace tricks::math;

void A_TperB(double **_A, double  **_B, double **_res,
			 int _righA, int _colA, int _righB, int _colB) {
	int p,q,l;                                      
	for (p=1;p<=_colA;p++)                        
		for (q=1;q<=_colB;q++)                        
		{ _res[p][q]=0.0;                            
			for (l=1;l<=_righA;l++)                    
				_res[p][q]=_res[p][q]+_A[l][p]*_B[l][q];  
		}                                            
}

//  Perform the Cholesky decomposition    
// Return the lower triangular L  such that L*L'=A  
void choldc(double **a, int n, double **l)
{
	int i,j,k;
	double sum;
	double *p = new double[n+1];
	
	for (i=1; i<=n; i++)  {
		for (j=i; j<=n; j++)  {
			for (sum=a[i][j],k=i-1;k>=1;k--) sum -= a[i][k]*a[j][k];
			if (i == j) {
				if (sum<=0.0)  
					// printf("\nA is not poitive definite!");
				{}
				else 
					p[i]=sqrt(sum); }
			else 
			{
				a[j][i]=sum/p[i];
			}
		}
	}       
	for (i=1; i<=n; i++)  
		for (j=i; j<=n; j++)  
			if (i==j)
				l[i][i] = p[i];
			else
			{
				l[j][i]=a[j][i];  
				l[i][j]=0.0;
			} 
	delete [] p;
}
void AperB(double **_A, double **_B, double **_res, 
		   int _righA, int _colA, int _righB, int _colB) {
	int p,q,l;                                      
	for (p=1;p<=_righA;p++)                        
		for (q=1;q<=_colB;q++)                        
		{ _res[p][q]=0.0;                            
			for (l=1;l<=_colA;l++)                     
				_res[p][q]=_res[p][q]+_A[p][l]*_B[l][q];  
		}                                            
}  

void AperB_T(double **_A, double **_B, double **_res,
			 int _righA, int _colA, int _righB, int _colB) {
	int p,q,l;                                      
	for (p=1;p<=_colA;p++)                         
		for (q=1;q<=_colB;q++)                        
		{ _res[p][q]=0.0;                            
			for (l=1;l<=_righA;l++)                    
				_res[p][q]=_res[p][q]+_A[p][l]*_B[q][l];  
		}                                            
}

#define	NEW_2D_FLOAT(A,x,y) A = new double*[x]; for(int i = 0; i < x; i++) {A[i] = new double[y]; memset(A[i], 0, sizeof(double)*y);}
#define DELETE_2D_FLOAT(A,x) for(int i = 0; i < x; i++) delete [] A[i]; delete [] A;

int inverse(double **TB, double **InvB, int N) {  
	int k,i,j,p,q;
	double mult;
	double D,temp;
	double maxpivot;
	int npivot;
	
	double **B; NEW_2D_FLOAT(B,N+1,N+2);
	double **A; NEW_2D_FLOAT(A,N+1,2*N+2);
	double **C; NEW_2D_FLOAT(C,N+1,N+1);
	
	double eps = 10e-20;
	
	
	for(k=1;k<=N;k++)
		for(j=1;j<=N;j++)
			B[k][j]=TB[k][j];
	
	for (k=1;k<=N;k++)
	{
		for (j=1;j<=N+1;j++)
			A[k][j]=B[k][j];
		for (j=N+2;j<=2*N+1;j++)
			A[k][j]=(float)0;
		A[k][k-1+N+2]=(float)1;
	}
	for (k=1;k<=N;k++)
	{
		maxpivot=ABS((double)A[k][k]);
		npivot=k;
		for (i=k;i<=N;i++)
			if (maxpivot<ABS((double)A[i][k]))
			{
				maxpivot=ABS((double)A[i][k]);
				npivot=i;
			}
		if (maxpivot>=eps)
	    {      if (npivot!=k)
			for (j=k;j<=2*N+1;j++)
			{
				temp=A[npivot][j];
				A[npivot][j]=A[k][j];
				A[k][j]=temp;
			} ;
			D=A[k][k];
			for (j=2*N+1;j>=k;j--)
				A[k][j]=A[k][j]/D;
			for (i=1;i<=N;i++)
			{
				if (i!=k)
				{
					mult=A[i][k];
					for (j=2*N+1;j>=k;j--)
						A[i][j]=A[i][j]-mult*A[k][j] ;
				}
			}
		}
		else
	    {  // printf("\n The matrix may be singular !!") ;
			DELETE_2D_FLOAT(B, N+1);
			DELETE_2D_FLOAT(A, N+1);
			DELETE_2D_FLOAT(C, N+1);
			return(-1);
		};
	}
	/**   Copia il risultato nella matrice InvB  ***/
	for (k=1,p=1;k<=N;k++,p++)
		for (j=N+2,q=1;j<=2*N+1;j++,q++)
			InvB[p][q]=A[k][j];

	DELETE_2D_FLOAT(B, N+1);
	DELETE_2D_FLOAT(A, N+1);
	DELETE_2D_FLOAT(C, N+1);
	return(0);
}      
/*  End of INVERSE   */



void ROTATE(double **a, int i, int j, int k, int l, double tau, double s) 
{
	double g,h;
	g=a[i][j];h=a[k][l];a[i][j]=g-s*(h+g*tau);
	a[k][l]=h+s*(g-h*tau);
}

void jacobi(double **a, int n, double *d , double **v, int nrot)      
{
	int j,iq,ip,i;
	double tresh,theta,tau,t,sm,s,h,g,c;
	
	double *b = new double[n+1];
	double *z = new double[n+1];
	
	
	for (ip=1;ip<=n;ip++) {
		for (iq=1;iq<=n;iq++) v[ip][iq]=0.0;
		v[ip][ip]=1.0;
	}
	for (ip=1;ip<=n;ip++) {
		b[ip]=d[ip]=a[ip][ip];
		z[ip]=0.0;
	}
	nrot=0;
	for (i=1;i<=50;i++) {
		sm=0.0;
		for (ip=1;ip<=n-1;ip++) {
			for (iq=ip+1;iq<=n;iq++)
				sm += ABS(a[ip][iq]);
		}
		if (sm == 0.0) {
			/*    free_vector(z,1,n);
			 free_vector(b,1,n);  */
			delete [] b;
			delete [] z;
			return;
		}
		if (i < 4)
			tresh=0.2*sm/(n*n);
		else
			tresh=0.0;
		for (ip=1;ip<=n-1;ip++) {
			for (iq=ip+1;iq<=n;iq++) {
				g=100.0*ABS(a[ip][iq]);
				if (i > 4 && ABS(d[ip])+g == ABS(d[ip])
					&& ABS(d[iq])+g == ABS(d[iq]))
					a[ip][iq]=0.0;
				else if (ABS(a[ip][iq]) > tresh) {
					h=d[iq]-d[ip];
					if (ABS(h)+g == ABS(h))
						t=(a[ip][iq])/h;
					else {
						theta=0.5*h/(a[ip][iq]);
						t=1.0/(ABS(theta)+sqrt(1.0+theta*theta));
						if (theta < 0.0) t = -t;
					}
					c=1.0/sqrt(1+t*t);
					s=t*c;
					tau=s/(1.0+c);
					h=t*a[ip][iq];
					z[ip] -= h;
					z[iq] += h;
					d[ip] -= h;
					d[iq] += h;
					a[ip][iq]=0.0;
					for (j=1;j<=ip-1;j++) {
						ROTATE(a,j,ip,j,iq,tau,s);
					}
					for (j=ip+1;j<=iq-1;j++) {
						ROTATE(a,ip,j,j,iq,tau,s);
					}
					for (j=iq+1;j<=n;j++) {
						ROTATE(a,ip,j,iq,j,tau,s);
					}
					for (j=1;j<=n;j++) {
						ROTATE(v,j,ip,j,iq,tau,s);
					}
					++nrot;
				}
			}
		}
		for (ip=1;ip<=n;ip++) {
			b[ip] += z[ip];
			d[ip]=b[ip];
			z[ip]=0.0;
		}
	}
	delete [] b;
	delete [] z;
}









void getPointsForConic(double *pvec, int nptsk, double **points)  {
	
	int npts=nptsk/2;	
	double **u; NEW_2D_FLOAT(u, 3, npts+1); //[][] = new double[3][npts+1];
	double **Aiu; NEW_2D_FLOAT(Aiu, 3, npts+1); //[][] = new double[3][npts+1];
	double **L; NEW_2D_FLOAT(L, 3, npts+1); //[][] = new double[3][npts+1];
	double **B; NEW_2D_FLOAT(B, 3, npts+1); //[][] = new double[3][npts+1];
	double **Xpos; NEW_2D_FLOAT(Xpos, 3, npts+1); //[][] = new double[3][npts+1];
	double **Xneg; NEW_2D_FLOAT(Xneg, 3, npts+1); //[][] = new double[3][npts+1];
	double **ss1; NEW_2D_FLOAT(ss1, 3, npts+1); //[][] = new double[3][npts+1];
	double **ss2; NEW_2D_FLOAT(ss2, 3, npts+1); //[][] = new double[3][npts+1];
	double *lambda = new double[npts+1];//lambda, 3, npts+1); //[] = new double[npts+1];
	double **uAiu; NEW_2D_FLOAT(uAiu, 3, npts+1); //[][] = new double[3][npts+1];
	
	
	
	double **A; NEW_2D_FLOAT(A, 3, 3); //[][] = new double[3][3];
	double **Ai; NEW_2D_FLOAT(Ai, 3, 3); //[][] = new double[3][3];
	double **Aib; NEW_2D_FLOAT(Aib, 3, 2); //[][] = new double[3][2];
	double **b; NEW_2D_FLOAT(b, 3, 2); //[][] = new double[3][2];
	double **r1; NEW_2D_FLOAT(r1, 3, 2); //[][] = new double[2][2];
	
	
	
	
	
	
	
	
	double Ao, Ax, Ay, Axx, Ayy, Axy;
	
	double pi = 3.14781;      
	double theta;
	int i;
	int j;
	double kk;
	
	Ao = pvec[6];
	Ax = pvec[4];
	Ay = pvec[5];
	Axx = pvec[1];
	Ayy = pvec[3];
	Axy = pvec[2];
	
	A[1][1] = Axx;    A[1][2] = Axy/2;
	A[2][1] = Axy/2;  A[2][2] = Ayy;
	b[1][1] = Ax; b[2][1] = Ay;  
	
	// Generate normals linspace
	for (i=1, theta=0.0; i<=npts; i++, theta+=(pi/npts)) {
		u[1][i] = cos(theta);
        u[2][i] = sin(theta); }
	
	inverse(A,Ai,2);
	
	AperB(Ai,b,Aib,2,2,2,1);
	A_TperB(b,Aib,r1,2,1,2,1);      
	r1[1][1] = r1[1][1] - 4*Ao;
	
	AperB(Ai,u,Aiu,2,2,2,npts);
	for (i=1; i<=2; i++)
		for (j=1; j<=npts; j++)
			uAiu[i][j] = u[i][j] * Aiu[i][j];
	
	for (j=1; j<=npts; j++) {
		if ( (kk=(r1[1][1] / (uAiu[1][j]+uAiu[2][j]))) >= 0.0)
			lambda[j] = sqrt(kk);
		else
			lambda[j] = -1.0; }
	
	// Builds up B and L
	for (j=1; j<=npts; j++)
		L[1][j] = L[2][j] = lambda[j];      
	for (j=1; j<=npts; j++) {
		B[1][j] = b[1][1];
		B[2][j] = b[2][1]; }
	
	for (j=1; j<=npts; j++) {
		ss1[1][j] = 0.5 * (  L[1][j] * u[1][j] - B[1][j]);
		ss1[2][j] = 0.5 * (  L[2][j] * u[2][j] - B[2][j]);
		ss2[1][j] = 0.5 * ( -L[1][j] * u[1][j] - B[1][j]);
		ss2[2][j] = 0.5 * ( -L[2][j] * u[2][j] - B[2][j]); }
	
	AperB(Ai,ss1,Xpos,2,2,2,npts);
	AperB(Ai,ss2,Xneg,2,2,2,npts);
	
	for (j=1; j<=npts; j++) {
		if (lambda[j]==-1.0) {
			points[1][j] = -1.0;
			points[2][j] = -1.0;
			points[1][j+npts] = -1.0;
			points[2][j+npts] = -1.0;
		}
		else {
			points[1][j] = Xpos[1][j];
			points[2][j] = Xpos[2][j];
			points[1][j+npts] = Xneg[1][j];
			points[2][j+npts] = Xneg[2][j];
		}	  	                 
	}
	DELETE_2D_FLOAT(u, 3);
	DELETE_2D_FLOAT(Aiu, 3);
	DELETE_2D_FLOAT(L, 3);
	DELETE_2D_FLOAT(B, 3);
	DELETE_2D_FLOAT(Xpos, 3);
	DELETE_2D_FLOAT(Xneg, 3);
	DELETE_2D_FLOAT(ss1, 3);
	DELETE_2D_FLOAT(ss2, 3);
	delete [] lambda;
	DELETE_2D_FLOAT(uAiu, 3);
	DELETE_2D_FLOAT(A, 3);
	DELETE_2D_FLOAT(Ai, 3);
	DELETE_2D_FLOAT(Aib, 3);
	DELETE_2D_FLOAT(b, 3);
	DELETE_2D_FLOAT(r1, 3);
	
}



void Ellipse::calcEllipse(vector<ofVec2f> &points) {
	
	
	
	int np = points.size();           // number of points
	
	if(np<6) return;
	
	
	
	
	double **D;		NEW_2D_FLOAT(D, np+1, 7);
	double **S;		NEW_2D_FLOAT(S, 7, 7);//[7][7];
	double **Const; NEW_2D_FLOAT(Const, 7, 7);//[7][7];
	double **temp;	NEW_2D_FLOAT(temp, 7, 7);//[7][7];
	double **L;		NEW_2D_FLOAT(L, 7, 7);//[7][7]; 
	double **C;		NEW_2D_FLOAT(C, 7, 7);//[7][7]; 
	
	double **invL;	NEW_2D_FLOAT(invL, 7, 7);//[7][7];
	double **V;		NEW_2D_FLOAT(V, 7, 7);//[7][7]; 
	double **sol;	NEW_2D_FLOAT(sol, 7, 7);//[7][7];
	
	
	
	double d[7];
	
	
	double tx,ty;
	int nrot=0;
	
	
	Const[1][3]=-2;
	Const[2][2]=1;
	Const[3][1]=-2;	
	
	
	
	
	// Now first fill design matrix
	for (int i=1; i <= np; i++) {
		
		tx = points[i-1].x;
		ty = points[i-1].y;
		D[i][1] = tx*tx;
		D[i][2] = tx*ty;
		D[i][3] = ty*ty;
		D[i][4] = tx;
		D[i][5] = ty;
		D[i][6] = 1.0;
	}
	
	
	// Now compute scatter matrix  S
	A_TperB(D,D,S,np,6,np,6);
	
	
	
	choldc(S,6,L);    
	
	inverse(L,invL,6);
	
	AperB_T(Const,invL,temp,6,6,6,6);
	AperB(invL,temp,C,6,6,6,6);
	
	
	jacobi(C,6,d,V,nrot);
	
	A_TperB(invL,V,sol,6,6,6,6);
	
	
	
	// Now normalize them 
	for (int j=1;j<=6;j++) { /* Scan columns */
		
		double mod = 0.0;
		for (int i=1;i<=6;i++)
			mod += sol[i][j]*sol[i][j];
		for (int i=1;i<=6;i++)
			sol[i][j] /=  sqrt(mod); 
	}
	
	
	
	
	double zero=10e-20;
	double minev=10e+20;
	int  solind=0;

	for (int i=1; i<=6; i++)
		if (d[i]<0 && ABS(d[i])>zero)	
			solind = i;
	
	// Now fetch the right solution
	for (int j=1;j<=6;j++)
		conicCoefficients[j] = sol[j][solind];
	
	
	
	
	DELETE_2D_FLOAT(D, np+1);
	DELETE_2D_FLOAT(S, 7);
	DELETE_2D_FLOAT(Const, 7);
	DELETE_2D_FLOAT(temp, 7);
	DELETE_2D_FLOAT(L, 7);
	DELETE_2D_FLOAT(C, 7);
	DELETE_2D_FLOAT(invL, 7);
	DELETE_2D_FLOAT(V, 7);
	DELETE_2D_FLOAT(sol, 7);
	
	
}




bool Ellipse::create(vector<ofVec2f> &points) {
	if(points.size()<6) return false;
	calcEllipse(points);
	
	
	// work out the parameters of the ellipse
	
	
	// to get the centre, we can add all the points and then make an average
	double **XY;	NEW_2D_FLOAT(XY, 3, NPTS+1);
	getPointsForConic(conicCoefficients,NPTS,XY);
	
	int numPoints = 0;
	double totalX = 0;
	double totalY = 0;
	
    // also find the boundingBox
    ofVec2f topLeft(1000,1000);
    ofVec2f bottomRight(0,0);
    
	for (int i=1; i<NPTS; i++) {
		if (XY[1][i]==-1 || XY[1][i+1]==-1  ) {
			continue;
		} else {
			if (i<NPTS) {
				numPoints++;
				totalX += XY[1][i];
				totalY += XY[2][i];
                
                if(topLeft.x>XY[1][i]) {
                    topLeft.x = XY[1][i];
                }
                if(topLeft.y>XY[2][i]) {
                    topLeft.y = XY[2][i];
                }
                
                if(bottomRight.x<XY[1][i]) {
                    bottomRight.x = XY[1][i];
                }
                if(bottomRight.y<XY[2][i]) {
                    bottomRight.y = XY[2][i];
                }
			}
		}
	}
	
    boundingBox.x = topLeft.x;
    boundingBox.y = topLeft.y;
    boundingBox.width = bottomRight.x - topLeft.x;
    boundingBox.height = bottomRight.y - topLeft.y;
    
	// here's the centre,
	centre.x = totalX/(double)numPoints;
	centre.y = totalY/(double)numPoints;
	
	// now work out the width, height and angle.
	
	// to do this, we work out the furthest and closest points to the centre
	float minDistSqr = FLT_MAX;
	float maxDistSqr = 0;
	ofVec2f minPt;
	ofVec2f maxPt;
	
	for (int i=1; i<NPTS; i++) {
		if (XY[1][i]==-1 || XY[1][i+1]==-1  ) {
			continue;
		} else {
			if (i<NPTS) {
				
				ofVec2f pt(XY[1][i],XY[2][i]);
				
				float distSqr = centre.distanceSquared(pt);
				
				if(distSqr<minDistSqr) {
					minPt = pt;
					minDistSqr = distSqr;
				} else if(distSqr>maxDistSqr) {
					maxPt = pt;
					maxDistSqr = distSqr;
				}
			}
		}
	}
	major = sqrt(maxDistSqr)*2;
	minor = sqrt(minDistSqr)*2;
	maxxy = maxPt;
	ofVec2f angleVec = maxPt - centre;
	angle = -angleVec.angle(ofVec2f(1, 0));

	DELETE_2D_FLOAT(XY, 3);
	
	calculateError(points);
	return true;
}


void Ellipse::calculateError(vector<ofVec2f> &points) {
	
	float totalError = 0;
	ofVec2f rightOfCentre = centre + ofVec2f(1, 0);
	maxError = 0;
	for(int i = 0; i < points.size(); i++) {
		float err = getError(points[i].x, points[i].y);
		totalError += err;
		if(err>maxError) maxError = err;
	}
	averageError = totalError/(float)points.size();
}

float Ellipse::getError(float x, float y) {
	ofVec2f a(x,y);
	ofVec2f d(1, 0);
	d.rotate(angle);
	
	ofVec2f c = centre + d;
	
	float pointAngle = angleBetweenPoints(a, centre, c);
	
	if(pointAngle<0) pointAngle *= -1;
	if(pointAngle>90) pointAngle = 180 - pointAngle;
	pointAngle = ofDegToRad(pointAngle);
	
	float ma = 0.5*minor*cos(pointAngle);
	float mb = 0.5*major*sin(pointAngle);
	float radius = 0.25*major*minor/sqrt(ma*ma + mb*mb );
	
	return ABS(a.distance(centre) - radius);
}

void Ellipse::draw() {
	ofEnableAlphaBlending();
	ofSetColor(0, 255, 0, 70);
	
	glPushMatrix();
	glTranslatef(centre.x, centre.y, 0);
	glRotatef(angle, 0, 0, 1);
	ofEllipse(0, 0, major, minor);
	ofSetHexColor(0xFF00FF);
	ofDrawBitmapString(ofToString(maxError, 2), 0, 0);
	glPopMatrix();
	
	/*
	ofSetHexColor(0xFF00FF);
	ofCircle(centre, 3);
	ofCircle(maxxy, 3);
	ofVec2f offset(100, 0);
	offset.rotate(angle);
	offset += centre;
	ofLine(centre, offset);*/
}

void Ellipse::getAABB(ofVec2f *p) {

	//printf("centre: %f %f    major %f     minor %f    angle %f\n", centre.x, centre.y, major, minor, angle);
	p[0] = centre + ofVec2f(-major/2, -minor/2).getRotated(angle);
	p[1] = centre + ofVec2f(major/2, -minor/2).getRotated(angle);
	p[2] = centre + ofVec2f(major/2, minor/2).getRotated(angle);
	p[3] = centre + ofVec2f(-major/2, minor/2).getRotated(angle);
}