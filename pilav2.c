//Pila 2, esta version ya contiene la función de Buscar.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int folio;
    int idClientes;
    double pesoKg;
    char origen[64];
    char destino[64];
    char fechaEnvio[11];
    char estado[16];
} Paquete;

typedef struct PaqStackNode {
    Paquete value;
    struct PaqStackNode* next;
} PaqStackNode;

typedef struct {
    PaqStackNode* top;
} PaqStack;

PaqStack* paq_stack_new(void) {
    PaqStack* pila = (PaqStack*) malloc(sizeof(PaqStack));
    pila->top = NULL;
    return pila;
}

int paq_stack_is_empty(const PaqStack* pila) {
    return pila->top == NULL;
}

int paq_stack_push(PaqStack* pila, Paquete* v) {
    PaqStackNode* nuevo = (PaqStackNode*) malloc(sizeof(PaqStackNode));
    if (!nuevo) return 0;
    nuevo->value = *v;
    nuevo->next = pila->top;
    pila->top = nuevo;
    return 1;
}

int paq_stack_pop(PaqStack* pila, Paquete* out) {
    if (paq_stack_is_empty(pila)) return 0;
    PaqStackNode* temp = pila->top;
    *out = temp->value;
    pila->top = temp->next;
    free(temp);
    return 1;
}

void paq_stack_free(PaqStack* pila) {
    PaqStackNode* aux;
    while (pila->top != NULL) {
        aux = pila->top;
        pila->top = aux->next;
        free(aux);
    }
    free(pila);
}

void paq_stack_mostrar(const PaqStack* pila) {
    if (paq_stack_is_empty(pila)) {
        printf("\nLa pila está vacía.\n");
        return;
    }
    printf("\nPaquetes en la pila:\n");
    PaqStackNode* actual = pila->top;
    while (actual) {
        Paquete p = actual->value;
        printf("Folio: %d | Cliente: %d | %.2f kg | %s -> %s | %s | %s\n",
               p.folio, p.idClientes, p.pesoKg, p.origen, p.destino, p.fechaEnvio, p.estado);
        actual = actual->next;
    }
}

PaqStackNode* paq_stack_buscar(PaqStack* pila, int folio) {
    PaqStackNode* actual = pila->top;
    while (actual) {
        if (actual->value.folio == folio) {
            return actual;
        }
        actual = actual->next;
    }
    return NULL;
}

int main() {
    PaqStack* pila = paq_stack_new();
    int opcion;
    Paquete p, temp;

    do {
        printf("\n===== MENU =====\n");
        printf("1. Agregar paquete\n");
        printf("2. Sacar paquete\n");
        printf("3. Mostrar pila\n");
        printf("4. Salir\n");
        printf("5. Buscar paquete por folio\n");
        printf("Elige una opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                printf("Folio: ");
                scanf("%d", &p.folio);
                printf("ID Cliente: ");
                scanf("%d", &p.idClientes);
                printf("Peso (kg): ");
                scanf("%lf", &p.pesoKg);
                getchar();

                printf("Origen: ");
                fgets(p.origen, 64, stdin);
                p.origen[strcspn(p.origen, "\n")] = '\0';

                printf("Destino: ");
                fgets(p.destino, 64, stdin);
                p.destino[strcspn(p.destino, "\n")] = '\0';

                printf("Fecha (dd/mm/yyyy): ");
                fgets(p.fechaEnvio, 11, stdin);
                p.fechaEnvio[strcspn(p.fechaEnvio, "\n")] = '\0';

                printf("Estado: ");
                fgets(p.estado, 16, stdin);
                p.estado[strcspn(p.estado, "\n")] = '\0';

                paq_stack_push(pila, &p);
                printf("\nPaquete agregado.\n");
                break;

            case 2:
                if (paq_stack_pop(pila, &temp)) {
                    printf("\nPaquete eliminado:\n");
                    printf("Folio: %d | %s -> %s | %.2f kg | %s\n",
                           temp.folio, temp.origen, temp.destino, temp.pesoKg, temp.estado);
                } else {
                    printf("\nLa pila está vacía.\n");
                }
                break;

            case 3:
                paq_stack_mostrar(pila);
                break;

            case 4:
                printf("\nSaliendo...\n");
                break;

            case 5:
                {
                    int folioBuscar;
                    printf("Ingrese el folio a buscar: ");
                    scanf("%d", &folioBuscar);
                    PaqStackNode* encontrado = paq_stack_buscar(pila, folioBuscar);
                    if (encontrado) {
                        Paquete p = encontrado->value;
                        printf("Paquete encontrado:\n");
                        printf("Folio: %d | Cliente: %d | %.2f kg | %s -> %s | %s | %s\n",
                               p.folio, p.idClientes, p.pesoKg, p.origen, p.destino, p.fechaEnvio, p.estado);
                    } else {
                        printf("No se encontró ningún paquete con ese folio.\n");
                    }
                }
                break;

            default:
                printf("\nOpción no válida.\n");
        }
    } while (opcion != 4);

    paq_stack_free(pila);
    return 0;
}
