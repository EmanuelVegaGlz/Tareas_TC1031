/*
 * Tareas TC1031.
 * Programación de estructuras de datos y algoritmos fundamentales
 * Grupo: 602
 * Profesor: Benjamín Valdés Aguirre.
 * Nombre: Emanuel Josué Vega González.
 * ID: A01710366.
 * 
 * Tarea 2: Algoritmos de Búsqueda y Ordenamiento
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

template <class T>
class Sorts{

    public:

        /**
         * Intercambia los valores de dos posiciones de un vector
         * 
         * @param v vector<T>: Vector, i int: Posición 1, j int: Posición 2
         * @return void
         * 
         */   
        void swap(vector<T> &v, int i, int j) {
            T aux = v[i];
            v[i] = v[j];
            v[j] = aux;
        }

        /**
         * Ordena un vector de menor a mayor con el algoritmo de selección
         * 
         * @param v vector<T>: Vector
         * @return void
         * 
         */
        void ordenaSeleccion(vector<T> &v){
            for(int i = 0; i < v.size(); i++){
                int min = i;
                for(int j = i; j < v.size(); j++){
                    if(v[min] > v[j])
                        min = j;
                }
                swap(v,i,min);
            }
        }
        
        /**
         * Ordena un vector de menor a mayor con el algoritmo de burbuja
         * 
         * @param v vector<T>: Vector
         * @return void
         * 
         */
        void ordenaBurbuja(vector<T> &v){
            for (int i = v.size() - 1; i > 0; i--) {
                for (int j = 0; j < i; j++) {
                    if (v[j] > v[j + 1]) {
                        swap(v, j, j + 1);
                    }
                }
            }
        }

        
        /**
         * Copia los valores de un vector a otro
         * 
         * @param A vector<T>: Vector original, B vector<T>: Vector copia, low int: Posición inicial, high int: Posición final
         * @return void
         * 
         */
        void copyArray(vector<T> &A, vector<T> &B, int low, int high) {
            for (int i = low; i <= high; i++) {
                A[i] = B[i];
            }
        }

        /**
         * Une dos vectores ordenados en uno solo
         * 
         * @param A vector<T>: Vector original, B vector<T>: Vector copia, low int: Posición inicial, mid int: Posición media, high int: Posición final
         * @return void
         * 
         */
        void mergeArray(vector<T> &A, vector<T> &B, int low, int mid, int high) {
            int i, j, k;

            i = low;
            j = mid + 1;
            k = low;

            while (i <= mid &&j <= high) {
                if (A[i] < A[j]) {
                    B[k] = A[i];
                    i++;
                } else {
                    B[k] = A[j];
                    j++;
                }
                k++;
            }
            if (i > mid) {
                for (; j <= high; j++) {
                    B[k++] = A[j];
                }
            } else {
                for (; i <= mid; i++) {
                    B[k++] = A[i];
                }
            }
        }

        /**
         * Divide el vector en dos partes y las ordena
         * 
         * @param A vector<T>: Vector original, B vector<T>: Vector copia, low int: Posición inicial, high int: Posición final
         * @return void
         * 
         */
        void mergeSplit(vector<T> &A, vector<T> &B, int low, int high) {
            int mid;

            if ( (high - low) < 1 ) {
                return;
            }
            mid = (high + low) / 2;
            mergeSplit(A, B, low, mid);
            mergeSplit(A, B, mid + 1, high);
            mergeArray(A, B, low, mid, high);
            copyArray(A, B, low, high);
        }

        /**
         * Ordena un vector de menor a mayor con el algoritmo de merge
         * 
         * @param v vector<T>: Vector
         * @return void
         * 
         */
        void ordenaMerge(vector<T> &v) {
            vector<T> tmp(v.size());

            mergeSplit(v, tmp, 0, v.size() - 1);
        }

        /**
         * Busca un valor en un vector de manera secuencial
         * 
         * @param v vector<T>: Vector, val int: Valor a buscar
         * @return int: Posición del valor
         * 
         */
        int busqSecuencial(vector<T>  v, int val) {
        for (int i = 0; i < v.size(); ++i) {
                if (v[i] == val) {
                    return i;
                }
            }
            return -1; 
        }

        /**
         * Mascara para la busqueda binaria
         * 
         * @param v vector<T>: Vector, val int: Valor a buscar, low int: Posición inicial, high int: Posición final
         * @return int: Posición del valor
         * 
         */
        int auxBs(vector<T> v, int val, int low, int high) {
            if (low > high) {
                return -1;
            }

            int mid = low + (high - low) / 2;

            if (v[mid] == val) {
                return mid;
            } else if (v[mid] < val) {
                return auxBs(v, val, mid + 1, high);
            } else {
                return auxBs(v, val, low, mid - 1);
            }
        }

        /**
         * Busca un valor en un vector de manera binaria
         * 
         * @param v vector<T>: Vector, val int: Valor a buscar
         * @return int: Posición del valor
         * 
         */
        int busqBinaria(vector<T> v, int val) {
            return auxBs(v, val, 0, v.size() - 1);

        }

};