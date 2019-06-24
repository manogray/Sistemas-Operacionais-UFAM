#define TAMBUCKET 256
#define fhash(i) (i*2654435761) % TAMBUCKET

using namespace std;

class Elemento{
    public:
        int valor;
        Elemento* proximo;

        Elemento(int valorRecebido);
        ~Elemento();
};

class Encadeada{
    public:
        
        Elemento* primeiro;     
        int ocupacao;

        Encadeada();

        void inserir(Elemento* elem);

        int buscar(int valorRecebido);

        int remover(Elemento* elem);

        ~Encadeada();
};

//Hash de inteiro,inteiro
class meuhash{
	Encadeada* tabelahash[TAMBUCKET];

	public:
		int ocupacao;
		meuhash();
		int get(int chave);
		void put(int chave,int val);
		~meuhash();	
};