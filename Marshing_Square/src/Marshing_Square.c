/*
 ============================================================================
 Name        : Marshing_Square.c
 Author      : Alexandre M. M.Filho
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

//Includes
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<GL/glut.h>

//-----------------------------------------------------------------------------Estruturas
/*
struct pontoGrade{
	int i, j;
	float valor;
};
*/
struct ponto{
	float x;
	float y;
	struct ponto *prox;
}ponto;

struct inicio{
	struct ponto* start;
	int total;
}inicio;

struct RGB{
	float R;
	float G;
	float B;
}RGB;

//------------------------------------------------------------------------------Protótipos
void init(void);
void display(void);
void keyboard(unsigned char, int, int);
void colorir(float,float);
void imprime(struct ponto);
void freeGeral(struct inicio*);
void criaPonto(struct inicio*,float,float);
void plotar(struct ponto, float*, float*);
void ajustesTela(int,int);
float transladar(float,float);
float escalar(float,float);
void pontilhado(void);
void gradeado(void);

//-----------------------------------------//Declarações e Inicializações de Variáveis Globais
float cordx=0.0, cordy=0.0,telax,telay,size_x=1.0,size_y=1.0;
int dl=0, dc=0, i, cont=0;
int tecla = 0, taxaescala;
struct inicio ini;
struct RGB cores;
//--------------------------------------------------------------------------Implementações

//-------------------------------------------------------------------------Pontilhado
void pontilhado(void){
	int lin, col;
	lin = dl+1;
	col = dc+1;
	glPointSize(3);
	glBegin(GL_POINTS);
	for(float i=0;i<col;i++)
	{
		for(float j=0;j<lin;j++)
		{
			glColor3f(0.0,0.0,0.0);
	  		glVertex2f(transladar(i,-1),transladar(j,-1));
		}
	}
	glEnd();
}

//-------------------------------------------------------------------------Gradeado
void gradeado(void){
	  int lin, col;
		  lin = dl;
		  col = dc;
		  glBegin(GL_LINES);
		  glColor3f(0.0,0.0,0.0);
		  	  for(float i=0;i<col+1;i++)
		  	  {
			  	  //glColor3f(0,0,0);
		  		  glVertex2f(transladar(i,-1),transladar(0,-1));
		  		  glVertex2f(transladar(i,-1),transladar(lin,-1));
		  	  }
		  	  for(float i=0;i<lin+1;i++)
		  	  {
		  		//glColor3f(0,0,0);
		  		glVertex2f(transladar(0,-1),transladar(i,-1));
		  		glVertex2f(transladar(col,-1),transladar(i,-1));
		  	  }
		  glScalef(0,taxaescala,0);
		  glEnd();
}

//-------------------------------------------------------------------------Transladar
float transladar(float x,float tx){
	return x = x + tx;
}

//-------------------------------------------------------------------------Escalar
float escalar(float x,float tx){
	return x = x*tx;
}
//-------------------------------------------------------------------------AjustesTela
void ajustesTela(int nl,int nc){
	size_x = 2/(nl+0.2);
	size_y = 2/(nc+0.2);
}

//------------------------------------------------------------------------------Plotar
void plotar(struct ponto first, float* px, float *py){
	  struct ponto *p;
	  p = &first;
	  float aux;
	  int ix;
	  glPointSize(3);
	  glBegin(GL_POINTS);

	  while(!(p == NULL)){
		  aux = p->x;
		  ix = aux;
		  aux = aux - ix;
		  aux = aux*10;
		  ix = aux;
		if(ix == 0){
		  	colorir(p->y,p->x);
		}else{
			colorir(p->x,p->y);
		}
		glColor3f(cores.R,cores.G,cores.B);
		//glColor3f(1.0,0.0,0.0);
		glVertex2f(transladar(p->x,-1),transladar(p->y,-1));
		//printf("%.6f %.6f\n",p->x,p->y);
	    p = p->prox;
	  }
	  glEnd();
}

//------------------------------------------------------------------------------Imprime
void imprime(struct ponto first){
	  struct ponto *p;
	  p = &first;
	  while(!(p == NULL)){
	    printf("%.6f %.6f\n",p->x,p->y);
	    p = p->prox;
	  }
}

//------------------------------------------------------------------------------FreeGeral
void freeGeral(struct inicio *apagar){
	  struct ponto *p , *pprox;
	  pprox = apagar->start;
	  while(!(pprox == NULL)){
	    p = pprox;
	    pprox = pprox->prox;
	    free(p);
	  }
	  free(pprox);
	  apagar->start = NULL;
	  apagar->total = 0;
}
//------------------------------------------------------------------------------CriaPonto
void criaPonto(struct inicio* No,float cx, float cy){
	struct ponto *novo;
	novo = (struct ponto*) malloc(sizeof(struct ponto));
	novo->x = cx;
	novo->y = cy;
	novo->prox = No->start;
	No->start = novo;
	No->total = No->total +1;
}
//------------------------------------------------------------------------------Colorir
void colorir(float cx,float cy){
  int inte = cx;
  float frac = cx;
  //printf("1-intex:%i  fracx:%f  cx:%f\n",inte,frac,cx);
    frac = frac - inte;
    frac = frac *10;
    inte = frac;
  //printf("2-intex:%i  fracx:%f\n",inte,frac);
	switch(inte){
	case 0:
		cores.R = 0.149;
		cores.G = 0.305;
		cores.B = 0.549;
		break;
	case 1:
		cores.R = 0.113;
		cores.G = 0.239;
		cores.B = 0.450;
		break;
	case 2:
		cores.R = 0.094;
		cores.G = 0.180;
		cores.B = 0.486;
		break;
	case 3:
		cores.R = 0.062;
		cores.G = 0.113;
		cores.B = 0.407;
		break;
	case 4:
		cores.R = 0.286;
		cores.G = 0.109;
		cores.B = 0.462;
		break;
	case 5:
		cores.R = 0.215;
		cores.G = 0.027;
		cores.B = 0.360;
		break;
	case 6:
		cores.R = 0.505;
		cores.G = 0.058;
		cores.B = 0.439;
		break;
	case 7:
		cores.R = 0.411;
		cores.G = 0.039;
		cores.B = 0.352;
		break;;
	case 8:
		cores.R = 0.721;
		cores.G = 0.125;
		cores.B = 0.086;
		break;
	case 9:
		cores.R = 0.560;
		cores.G = 0.090;
		cores.B = 0.019;
		break;
	}
	glColor3f(cores.R,cores.G,cores.B);
}
//------------------------------------------------------------------------------Init
void init(void)
{
  glOrtho (-1.1, (telay+0.1)-1,-1.1,(telax+0.1)-1, -1 ,1);
  //glOrtho (-1.1, (telay+0.1)-1,(telax+0.1)-1,-1.1, -1 ,1);
  glClearColor(0.5, 0.5, 0.5, 1.0);
  glFlush();
}
//------------------------------------------------------------------------------Display
void display(void){

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glFlush();
	//Apenas Pontos
	if(tecla ==1){
		pontilhado();
	}
	//Apenas Grade
	if(tecla == 2){
		gradeado();
	 }
	//Fundo pontilhado e pontos do arquivo
	if(tecla == 3){
		pontilhado();
		plotar(*ini.start, &cordx,&cordy);
	}
	//Fundo Gradeado e pontos do arquivo
	if(tecla == 4){
		  gradeado();
		glPointSize(3);
		glBegin(GL_POINTS);
		plotar(*ini.start, &cordx,&cordy);
		glEnd();
	}
	//Fundo pontilhado e linhas do arquivo
	if(tecla == 5){
			pontilhado();
			glPointSize(3);
			glBegin(GL_LINES);
			plotar(*ini.start, &cordx,&cordy);
			glEnd();
		}
		//fundo gradeado e linhas do arquivo
		if(tecla == 6){
			  gradeado();
			  glEnd();
			  glFlush();
			glPointSize(3);
			glBegin(GL_LINES);
			plotar(*ini.start, &cordx,&cordy);
			glEnd();
		}

		//Preenchimento em L
	  if(tecla == 10){
	  		  int lin, col;
	  		  lin = 7;
	  		  col = 5;
	  		  glBegin(GL_LINES);
	  		  //Linha
	  		  for(int i=0;i<lin;i++)
	  		  {
	  			  //Coluna
	  			  for(int j=0;j<col;j++)
	  			  {
	  				  glColor3f(1,0,0);
	  				  glVertex2f(j,i); //p0 horizontal
	  				  glVertex2f(j+1,i);
	  				  glVertex2f(j,i); //p0 vertical
	  				  glVertex2f(j,i+1);
	  			  }
	  		  }
	  		  //Coloca linhas finalizadoras (complexidade [N*N])

	  		  glVertex2f(col,lin);
	  		  glVertex2f(0,lin);
	  		  glVertex2f(col,lin);
	  		  glVertex2f(col,0);

	  		  glEnd();
	  	  }

	glFlush();
}
//------------------------------------------------------------------------------keyboard
void keyboard( unsigned char key, int x, int y )
{
	switch( key ) {

	case 'q' : case 'Q' :
		tecla = 1;
		break;

	case 'w' : case 'W' :
		tecla = 2;
		break;

	case 'a' : case 'A' :
		tecla = 3;
		break;

	case 's' : case 'S' :
		tecla = 4;
		break;

	case 'z' : case 'Z' :
		tecla = 5;
		break;

	case 'x' : case 'X' :
		tecla = 6;
		break;
	}
		display();
}

//------------------------------------------------------------------------------Main
int main(int argc, char** argv) {
	cores.R = 0.0;
	cores.G = 0.0;
	cores.B = 0.0;
/*
	telax = 1;
	telay = 1;
*/
	ini.start = NULL;
	ini.total = 0;

	char linha[1024], *pch = NULL;
	FILE *fp=NULL;
	char nome[80];
	printf("Digite o nome da matriz fonte a ser lida:\n");
	 	  	  scanf("%s",nome);
	 	  	  fp = fopen(nome,"r");
	 	  	  if(fp == NULL){
	 	  		  printf("Arquivo inexistente.\n");
	 	  	  }

	 		  //Pega dimensão da matriz
	 		  	    fgets(linha,1024,fp);
	 		  	    pch = strtok(linha," x\n");
	 		  	    dl = atoi(pch);
	 		  	    pch = strtok(NULL," x\n");
	 		  	    dc = atoi(pch);
	 		  	    ajustesTela(dl,dc);
	 		  	    printf("%d %d\n",dl,dc);
	 		  	    telax = dl;
	 		  	    telay = dc;
	 		  	    taxaescala = 0;


	 		  	    /*
	 		  	    //Contagem de pontos da matriz
	 		  	    cont = 1;
	 		  	    for(i=0;!feof(fp);i++){
	 		  	    	fgets(linha,1024,fp);
	 		  	    	cont++;
	 		  	    }
	 		  	    cont=cont-2;
	 		  	  printf("cont %d\n",cont);

	 		  	    rewind(fp);
	 		  	    fgets(linha,1024,fp);
	 		  	    printf("%s",linha);

	 		  	    printf("total %d\n",ini.total);

	 		  	    */
	 		  	  //Pega valores e coloca na lista en
	 		  	  for(i=1,fgets(linha,1024,fp);i<cont,!feof(fp);fgets(linha,1024,fp),i++){
	 		  		  printf("linha %s\n",linha);
	 		  		  pch = strtok(linha," \n");
	 		  		  cordx = atof(pch);
	 		  		  printf("x %f\n",cordx);
	 		  		  pch = strtok(NULL," \n");
	 		  		  cordy = atof(pch);
	 		  		  printf("y %f\n",cordy);
	 		  		  criaPonto(&ini,cordx,cordy);
	 		  		  }
	 		  	  printf("total %d\n",ini.total);
	 		  	  imprime(*ini.start);

	 //Inicializa a biblioteca GLUT e negocia uma seção com o gerenciador de janelas.
	 //É possível passar argumentos para a função glutInit provenientes da linha de execução, tais como informações sobre a geometria da tela
	  glutInit(&argc, argv);

	  //Informa à biblioteca GLUT o modo do display a ser utilizado quando a janela gráfica for criada.
	  // O flag GLUT_SINGLE força o uso de uma janela com buffer simples, significando que todos os desenhos serão feitos diretamente nesta janela.
	  // O flag GLUT_RGB determina que o modelo de cor utilizado será o modelo RGB.
	  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

	  //Define o tamanho inicial da janela, 256x256 pixels, e a posição inicial do seu canto superior esquerdo na tela, (x, y)=(100, 100).
	  glutInitWindowSize (800,800);
	  glutInitWindowPosition (283, 84);

	  // Cria uma janela e define seu título
	  glutCreateWindow ("Marching Squares");

	  //Nesta função é definido o estado inicial do OpenGL. Ajustes podem ser feitos para o usuário nessa função.
	  init();

	  // Define display() como a função de desenho (display callback) para a janela corrente.
	  // Quando GLUT determina que esta janela deve ser redesenhada, a função de desenho é chamada.
	  glutDisplayFunc(display);

	  // Indica que sempre que uma tecla for pressionada no teclado, GLUT deverá chama a função keyboard() para tratar eventos de teclado (keyboard callback).
	  // A função de teclado deve possuir o seguinte protótipo:
	  glutKeyboardFunc(keyboard);

	  //Inicia o loop de processamento de desenhos com GLUT.
	  // Esta rotina deve ser chamada pelo menos uma vez em um programa que utilize a biblioteca GLUT.
	  glutMainLoop();

	  freeGeral(&ini);
	  return EXIT_SUCCESS;

}
