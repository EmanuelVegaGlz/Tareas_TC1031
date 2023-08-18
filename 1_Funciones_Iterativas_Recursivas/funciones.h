class Funciones{
    public:
    int sumaIterativa(int num){
        int acum = 0;
        for(int i = 1; i <= num; i++){
            acum += i;
        }
        return acum;
    }

    int sumaRecursiva(int num){
        if(num == 0)
	        return 0;

        else 
            return num + sumaRecursiva(num - 1);
    }

    int sumaDirecta(int num){
        return (num*(num+1))/2;
    }

};