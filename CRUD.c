#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;
    char nome[50];
    char email[50];
    char sexo[15];
    char endereco[100];
    double altura;
    int vacina;
} Usuario;

int totalUsuarios = 0;
Usuario *usuarios = NULL;

// Função para gerar um número aleatório para o ID
int gerarId() {
    return rand() % 1000 + 1;
}

// Função para validar o email
int validarEmail(const char *email) {
    const char *arroba = strchr(email, '@');
    return (arroba != NULL);
}

// Função para validar o sexo
int validarSexo(const char *sexo) {
    return (strcmp(sexo, "Feminino") == 0 || strcmp(sexo, "Masculino") == 0 || strcmp(sexo, "Indiferente") == 0);
}

// Função para validar a altura
int validarAltura(double altura) {
    return (altura >= 1.0 && altura <= 2.0);
}

// Função para cadastrar um novo usuário
void cadastrarUsuario() {
    Usuario usuario;

    printf("Nome completo: ");
    fgets(usuario.nome, sizeof(usuario.nome), stdin);
    usuario.nome[strcspn(usuario.nome, "\n")] = '\0';

    printf("Email: ");
    fgets(usuario.email, sizeof(usuario.email), stdin);
    usuario.email[strcspn(usuario.email, "\n")] = '\0';

    while (!validarEmail(usuario.email)) {
        printf("Email invalido. Digite novamente: ");
        fgets(usuario.email, sizeof(usuario.email), stdin);
        usuario.email[strcspn(usuario.email, "\n")] = '\0';
    }

    printf("Sexo (Feminino/Masculino/Indiferente): ");
    fgets(usuario.sexo, sizeof(usuario.sexo), stdin);
    usuario.sexo[strcspn(usuario.sexo, "\n")] = '\0';

    while (!validarSexo(usuario.sexo)) {
        printf("Sexo invalido. Digite novamente: ");
        fgets(usuario.sexo, sizeof(usuario.sexo), stdin);
        usuario.sexo[strcspn(usuario.sexo, "\n")] = '\0';
    }

    printf("Endereco: ");
    fgets(usuario.endereco, sizeof(usuario.endereco), stdin);
    usuario.endereco[strcspn(usuario.endereco, "\n")] = '\0';

    printf("Altura (1-2 m): ");
    scanf("%lf", &usuario.altura);
    getchar();

    while (!validarAltura(usuario.altura)) {
        printf("Altura invalida. Digite novamente: ");
        scanf("%lf", &usuario.altura);
        getchar();
    }

    printf("Vacina (1 - Sim / 0 - Nao): ");
    scanf("%d", &usuario.vacina);
    getchar();

    usuario.id = gerarId();

    totalUsuarios++;
    usuarios = realloc(usuarios, totalUsuarios * sizeof(Usuario));
    usuarios[totalUsuarios - 1] = usuario;

    printf("Usuario cadastrado com sucesso!\n");
}

// Função para buscar um usuário pelo ID
Usuario *buscarUsuarioPorId(int id) {
    for (int i = 0; i < totalUsuarios; i++) {
        if (usuarios[i].id == id) {
            return &usuarios[i];
        }
    }
    return NULL;
}

// Função para buscar um usuário pelo nome
Usuario *buscarUsuarioPorNome(const char *nome) {
    for (int i = 0; i < totalUsuarios; i++) {
        if (strcmp(usuarios[i].nome, nome) == 0) {
            return &usuarios[i];
        }
    }
    return NULL;
}

// Função para buscar um usuário pelo email
Usuario *buscarUsuarioPorEmail(const char *email) {
    for (int i = 0; i < totalUsuarios; i++) {
        if (strcmp(usuarios[i].email, email) == 0) {
            return &usuarios[i];
        }
    }
    return NULL;
}

// Função para listar todos os usuários
void listarUsuarios() {
    if (totalUsuarios == 0) {
        printf("Nenhum usuario cadastrado.\n");
        return;
    }

    printf("Lista de usuarios:\n");
    for (int i = 0; i < totalUsuarios; i++) {
        printf("ID: %d\n", usuarios[i].id);
        printf("Nome: %s\n", usuarios[i].nome);
        printf("Email: %s\n", usuarios[i].email);
        printf("Sexo: %s\n", usuarios[i].sexo);
        printf("Endereco: %s\n", usuarios[i].endereco);
        printf("Altura: %.2lf\n", usuarios[i].altura);
        printf("Vacina: %s\n", usuarios[i].vacina ? "Sim" : "Nao");
        printf("--------------------------\n");
    }
}

// Função para remover um usuário pelo ID
void removerUsuarioPorId(int id) {
    int index = -1;
    for (int i = 0; i < totalUsuarios; i++) {
        if (usuarios[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Usuario nao encontrado.\n");
        return;
    }

    // Movendo os usuários à direita do usuário removido para preencher o espaço vazio
    for (int i = index; i < totalUsuarios - 1; i++) {
        usuarios[i] = usuarios[i + 1];
    }

    totalUsuarios--;
    usuarios = realloc(usuarios, totalUsuarios * sizeof(Usuario));

    printf("Usuario removido com sucesso!\n");
}

// Função para editar um usuário
void editarUsuario(Usuario *usuario) {
    printf("Escolha o dado a ser alterado:\n");
    printf("1. Nome\n");
    printf("2. Email\n");
    printf("3. Sexo\n");
    printf("4. Endereco\n");
    printf("5. Altura\n");
    printf("6. Vacina\n");

    int opcao;
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1: {
            printf("Novo nome: ");
            fgets(usuario->nome, sizeof(usuario->nome), stdin);
            usuario->nome[strcspn(usuario->nome, "\n")] = '\0';
            break;
        }
        case 2: {
            printf("Novo email: ");
            fgets(usuario->email, sizeof(usuario->email), stdin);
            usuario->email[strcspn(usuario->email, "\n")] = '\0';
            while (!validarEmail(usuario->email)) {
                printf("Email invalido. Digite novamente: ");
                fgets(usuario->email, sizeof(usuario->email), stdin);
                usuario->email[strcspn(usuario->email, "\n")] = '\0';
            }
            break;
        }
        case 3: {
            printf("Novo sexo (Feminino/Masculino/Indiferente): ");
            fgets(usuario->sexo, sizeof(usuario->sexo), stdin);
            usuario->sexo[strcspn(usuario->sexo, "\n")] = '\0';
            while (!validarSexo(usuario->sexo)) {
                printf("Sexo invalido. Digite novamente: ");
                fgets(usuario->sexo, sizeof(usuario->sexo), stdin);
                usuario->sexo[strcspn(usuario->sexo, "\n")] = '\0';
            }
            break;
        }
        case 4: {
            printf("Novo endereco: ");
            fgets(usuario->endereco, sizeof(usuario->endereco), stdin);
            usuario->endereco[strcspn(usuario->endereco, "\n")] = '\0';
            break;
        }
        case 5: {
            printf("Nova altura (1-2 m): ");
            scanf("%lf", &usuario->altura);
            getchar();
            while (!validarAltura(usuario->altura)) {
                printf("Altura invalida. Digite novamente: ");
                scanf("%lf", &usuario->altura);
                getchar();
            }
            break;
        }
        case 6: {
            printf("Vacina (1 - Sim / 0 - Nao): ");
            scanf("%d", &usuario->vacina);
            getchar();
            break;
        }
        default:
            printf("Opcao invalida.\n");
            return;
    }

    printf("Usuario atualizado com sucesso!\n");
}

int main() {
    int opcao;

    do {
        printf("----------- MENU -----------\n");
        printf("1. Cadastrar usuario\n");
        printf("2. Consultar usuario\n");
        printf("3. Listar usuarios\n");
        printf("4. Remover usuario\n");
        printf("5. Editar usuario\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarUsuario();
                break;
            case 2: {
                int consultaOpcao;
                printf("Consultar usuario por:\n");
                printf("1. ID\n");
                printf("2. Nome\n");
                printf("3. Email\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &consultaOpcao);
                getchar();

                switch (consultaOpcao) {
                    case 1: {
                        int id;
                        printf("Digite o ID do usuario: ");
                        scanf("%d", &id);
                        getchar();

                        Usuario *usuario = buscarUsuarioPorId(id);
                        if (usuario != NULL) {
                            printf("Usuario encontrado:\n");
                            printf("ID: %d\n", usuario->id);
                            printf("Nome: %s\n", usuario->nome);
                            printf("Email: %s\n", usuario->email);
                            printf("Sexo: %s\n", usuario->sexo);
                            printf("Endereco: %s\n", usuario->endereco);
                            printf("Altura: %.2lf\n", usuario->altura);
                            printf("Vacina: %s\n", usuario->vacina ? "Sim" : "Nao");
                        } else {
                            printf("Usuario nao encontrado.\n");
                        }
                        break;
                    }
                    case 2: {
                        char nome[50];
                        printf("Digite o nome do usuario: ");
                        fgets(nome, sizeof(nome), stdin);
                        nome[strcspn(nome, "\n")] = '\0';

                        Usuario *usuario = buscarUsuarioPorNome(nome);
                        if (usuario != NULL) {
                            printf("Usuario encontrado:\n");
                            printf("ID: %d\n", usuario->id);
                            printf("Nome: %s\n", usuario->nome);
                            printf("Email: %s\n", usuario->email);
                            printf("Sexo: %s\n", usuario->sexo);
                            printf("Endereo: %s\n", usuario->endereco);
                            printf("Altura: %.2lf\n", usuario->altura);
                            printf("Vacina: %s\n", usuario->vacina ? "Sim" : "Nao");
                        } else {
                            printf("Usuario nao encontrado.\n");
                        }
                        break;
                    }
                    case 3: {
                        char email[50];
                        printf("Digite o email do usuario: ");
                        fgets(email, sizeof(email), stdin);
                        email[strcspn(email, "\n")] = '\0';

                        Usuario *usuario = buscarUsuarioPorEmail(email);
                        if (usuario != NULL) {
                            printf("Usuario encontrado:\n");
                            printf("ID: %d\n", usuario->id);
                            printf("Nome: %s\n", usuario->nome);
                            printf("Email: %s\n", usuario->email);
                            printf("Sexo: %s\n", usuario->sexo);
                            printf("Endereco: %s\n", usuario->endereco);
                            printf("Altura: %.2lf\n", usuario->altura);
                            printf("Vacina: %s\n", usuario->vacina ? "Sim" : "Nao");
                        } else {
                            printf("Usuario nao encontrado.\n");
                        }
                        break;
                    }
                    default:
                        printf("Opcao invalida.\n");
                        break;
                }

                break;
            }
            case 3:
                listarUsuarios();
                break;
            case 4: {
                int remocaoOpcao;
                printf("Remover usuario por:\n");
                printf("1. ID\n");
                printf("2. Nome\n");
                printf("3. Email\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &remocaoOpcao);
                getchar();

                switch (remocaoOpcao) {
                    case 1: {
                        int id;
                        printf("Digite o ID do usuario a ser removido: ");
                        scanf("%d", &id);
                        getchar();
                        removerUsuarioPorId(id);
                        break;
                    }
                    case 2: {
                        char nome[50];
                        printf("Digite o nome do usuario a ser removido: ");
                        fgets(nome, sizeof(nome), stdin);
                        nome[strcspn(nome, "\n")] = '\0';

                        Usuario *usuario = buscarUsuarioPorNome(nome);
                        if (usuario != NULL) {
                            removerUsuarioPorId(usuario->id);
                        } else {
                            printf("Usuario nao encontrado.\n");
                        }
                        break;
                    }
                    case 3: {
                        char email[50];
                        printf("Digite o email do usuario a ser removido: ");
                        fgets(email, sizeof(email), stdin);
                        email[strcspn(email, "\n")] = '\0';

                        Usuario *usuario = buscarUsuarioPorEmail(email);
                        if (usuario != NULL) {
                            removerUsuarioPorId(usuario->id);
                        } else {
                            printf("Usuario nao encontrado.\n");
                        }
                        break;
                    }
                    default:
                        printf("Opcao invalida.\n");
                        break;
                }

                break;
            }
            case 5: {
                int edicaoOpcao;
                printf("Editar usuario por:\n");
                printf("1. ID\n");
                printf("2. Nome\n");
                printf("3. Email\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &edicaoOpcao);
                getchar();

                switch (edicaoOpcao) {
                    case 1: {
                        int id;
                        printf("Digite o ID do usuario a ser editado: ");
                        scanf("%d", &id);
                        getchar();

                        Usuario *usuario = buscarUsuarioPorId(id);
                        if (usuario != NULL) {
                            editarUsuario(usuario);
                        } else {
                            printf("Usuario nao encontrado.\n");
                        }
                        break;
                    }
                    case 2: {
                        char nome[50];
                        printf("Digite o nome do usuario a ser editado: ");
                        fgets(nome, sizeof(nome), stdin);
                        nome[strcspn(nome, "\n")] = '\0';

                        Usuario *usuario = buscarUsuarioPorNome(nome);
                        if (usuario != NULL) {
                            editarUsuario(usuario);
                        } else {
                            printf("Usuario nao encontrado.\n");
                        }
                        break;
                    }
                    case 3: {
                        char email[50];
                        printf("Digite o email do usuario a ser editado: ");
                        fgets(email, sizeof(email), stdin);
                        email[strcspn(email, "\n")] = '\0';

                        Usuario *usuario = buscarUsuarioPorEmail(email);
                        if (usuario != NULL) {
                            editarUsuario(usuario);
                        } else {
                            printf("Usuario nao encontrado.\n");
                        }
                        break;
                    }
                    default:
                        printf("Opcao invalida.\n");
                        break;
                }

                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }

        printf("-----------------------------\n\n");
    } while (opcao != 0);

    // Liberando a memória alocada
    free(usuarios);

    return 0;
}