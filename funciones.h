/*
 * Tareas TC1031.
 * Programación de estructuras de datos y algoritmos fundamentales
 * Grupo: 602
 * Profesor: Benjamín Valdés Aguirre.
 * Nombre: Emanuel Josué Vega González.
 * ID: A01710366.
 * 
 * Tarea 1: Funciones iterativas y recursivas
 */

class Funciones{
    public:

    /**
     *  Calcula la sumatoria de 1 hasta n con un ciclo for
     * 
     * @param num int: num
     * @return acum, int: Sumatoria
     */
    int sumaIterativa(int num){
        int acum = 0;
        for(int i = 1; i <= num; i++){
            acum += i;
        }
        return acum;
    }

    /**
     *  Calcula la sumatoria de 1 hasta n de manera iterativa
     * 
     * @param num int: num
     * @return La sumatoria de las llamadas recursivas
     */
    int sumaRecursiva(int num){
        if(num == 0)
	        return 0;
        else
            return num + sumaRecursiva(num - 1);
    }

    /**
     *  Calcula la sumatroia  sin ciclos
     * 
     * @param num int: num
     * @return acum, int: Sumatoria
     */
    int sumaDirecta(int num){
        return (num*(num+1))/2;
    }

};