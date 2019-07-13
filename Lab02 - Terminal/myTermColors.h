#ifndef TERMCOR_H
#define TERMCOR_H

#define foreground(color) FORE##color
#define background(color) BACK##color
#define style(style_) style_

/** Cores de Primeiro Plano: Foreground **/
#define FOREPRETO printf("\033[1;30m") 
#define FOREVERMELHO printf("\033[1;31m") 
#define FOREVERDE printf("\033[1;32m") 
#define FOREAMARELO printf("\033[1;33m") 
#define FOREAZUL printf("\033[1;34m") 
#define FOREMARGENTA printf("\033[1;35m") 
#define FORECIANO printf("\033[1;36m") 
#define FOREBRANCO printf("\033[0;37m") 
#define FORENORMAL_COR printf("\033[1;39m") 

/**Cores de Fundo: Background **/
#define BACKPRETO printf("\033[40m") 
#define BACKVERMELHO printf("\033[41m") 
#define BACKVERDE printf("\033[42m") 
#define BACKAMARELO printf("\033[43m") 
#define BACKAZUL printf("\033[44m") 
#define BACKMAGENTA printf("\033[45m") 
#define BACKCIANO printf("\033[46m") 
#define BACKBRANCO printf("\033[47m") 
#define BACKNORMAL printf("\033[49m")

/** Estilos de Fonte: Style **/
#define BRIGHT printf("\033[1m")
#define DIM printf("\033[2m")
#define NORMAL printf("\033[22m")
#define RESETALL printf("\033[0m")
#define UNDERLINE printf("\033[4m")
#define BLINKSLOW printf("\033[5m")
#define BLINKRAPID printf("\033[6m")
#define ITALIC printf("\033[3m")
#define NEGATIVE printf("\033[7m")

#endif /* TERMCOR_H */