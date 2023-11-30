# Tareas_TC1031

## Programación de estructuras de datos y algoritmos fundamentales
 * **Profesor:** Benjamín Valdés Aguirre.
 * **Nombre:** Emanuel Josué Vega González.
 * **ID:** A01710366
 * **Grupo:** 602

## Correcciones

### Árbol Heap
Se corrige esta tarea ya que en la primera entrega se implementa tanto el min como el max heap ya que en las especificaciones de calendario se pedía un max heap, sin embargo, en el main que se prueba es para un min heap. Por lo tanto, no pasaba algunos casos de prueba, en esta entrega se carga únicamente el min heap.

### Spaly Tree
Se modificó la función find() de la clase Node, el cambio se hizo en la línea 97, en donde se devuelve un apuntador vacío si no se entra a los condicionales, para asegurar que devuelva un valor válido. Como la función está declarada para devolver un apuntador de la clase Node había situaciones donde la función no retornaba un valor, lo cual podía causar errores de segmentación. De igual forma el remove tenia errores de logica, teniendo problemas de segmentation fault. La correccion esta de la linea 342 a la 362.
