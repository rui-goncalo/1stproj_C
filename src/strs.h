/**
 * @file strs.h
 * @author Micael Dias, Hugo Carvalho, Rui Gonçalves
 * @date 8/1/2021
 * @brief Standardized strings
 */

#ifndef STRS_H
#define STRS_H

#include "colors.h"

// Globals
#define H_STRS_MENU_CHOICE GREEN("> ")
#define H_STRS_INVALID_INPUT RED("[!] Input Inválido")
#define H_STRS_MALLOC_FAILED RED("[!] Não foi possível alocar espaço")
#define H_STRS_MISSING_CAPACITY RED("[!] Tamanho inicial não definido")
#define H_STRS_PARSE_ERROR RED("[!] Software não esta pronto para executar o parsing")
#define H_STRS_LOAD_SUCCESS GREEN("[!] Ficheiro carregado com sucesso")
#define H_STRS_LOAD_FAILED RED("[!] Falha ao carregar o ficheiro")
#define H_STRS_LOAD_REPLACE RED("[!] Já existiam dados na tabela. Novos foram carregados")
#define H_STRS_SAVE_SUCCESS GREEN("[!] Guardado com Sucesso")
#define H_STRS_SAVE_FILE_ERROR RED("[!] Não foi possível guardar o ficheiro")
#define H_STRS_PATH_MISSING RED("[!] A localização do ficheiro não foi especificada")
#define H_STRS_FILE_NOT_FOUND RED("[!] Ficheiro não encontrado")

#define H_STRS_EDIT YELLOW("Linha a editar:")
#define H_STRS_DELETE YELLOW("Linha a eliminar:")
#define H_STRS_EMPTY_TABLE RED("[!] Tabela Vazia\n")

// Employees
#define H_STRS_EMPLOYEES_ERROR_INIT RED("Fúncionarios não inicializados")

// IRS
#define H_STRS_IRS_ERROR_INIT RED("Tabela IRS não inicializada")

// ISS
#define H_STRS_NEW_CRITERIA YELLOW("Novo critério: ")
#define H_STRS_CRITERIA_DUPLICATE RED("[!] Já existe um critério com esse nome. Abortar...\n")
#define H_STRS_ISS_ERROR_INIT RED("[!] Tabela ISS não inicializada")

// PROC
#define H_STRS_EMPLOYEES_NOT_FOUND RED("[!] Nenhum funcionário encontrado")
#define H_STRS_MONTH_NOT_CREATED RED("[!] Nenhum mês foi criado")
#define H_STRS_ALREADY_PROCESSED RED("[!] Mês já processado")
#define H_STRS_ALREADY_CREATED RED("[!] Mês já foi criado")
#define H_STRS_PROCESSED_SUCCESS GREEN("[!] Mês processado com sucesso")

#define H_STRS_MENU BLUE( \
"*********************************\n" \
"*         -|  MENU  |-          *\n" \
"*                               *\n" \
"* 1. Tabelas Retenção IRS       *\n" \
"* 2. Tabelas Segurança Social   *\n" \
"* 3. Gestão de Funcionários     *\n" \
"* 4. Processar Salarios         *\n" \
"* 5. Relatórios                 *\n" \
"* 8. Carregar todas as tabelas  *\n" \
"* 9. Guardar Tudo               *\n" \
"* 0. Sair                       *\n" \
"*                               *\n" \
"*********************************\n")

#define H_STRS_IRS_MENU BLUE( \
"*****************************************************\n" \
"*         -| Menu Tabelas de Retenção IRS |-        *\n" \
"*                                                   *\n" \
"*  TABELAS DE RETENÇÃO NA FONTE PARA O CONTINENTE   *\n" \
"*                                                   *\n" \
"*                TRABALHO DEPENDENTE                *\n" \
"*                                                   *\n" \
"* -| Tabela I - NÃO CASADO |-                       *\n" \
"*  1. Carregar Tabela                               *\n" \
"*  2. Visualizar                                    *\n" \
"*  3. Editar                                        *\n" \
"*  4. Adicionar                                     *\n" \
"*  5. Eliminar                                      *\n" \
"*  6. Guardar                                       *\n" \
"*                                                   *\n" \
"* -| Tabela II - CASADO UNICO TITULAR |-            *\n" \
"*  7. Carregar Tabela                               *\n" \
"*  8. Visualizar                                    *\n" \
"*  9. Editar                                        *\n" \
"* 10. Adicionar                                     *\n" \
"* 11. Eliminar                                      *\n" \
"* 12. Guardar                                       *\n" \
"*                                                   *\n" \
"* -| Tabela III - CASADO DOIS TITULAR |-            *\n" \
"* 13. Carregar Tabela                               *\n" \
"* 14. Visualizar                                    *\n" \
"* 15. Editar                                        *\n" \
"* 16. Adicionar                                     *\n" \
"* 17. Eliminar                                      *\n" \
"* 18. Guardar                                       *\n" \
"*                                                   *\n" \
"* 0. Voltar ao menu anterior                        *\n" \
"*                                                   *\n" \
"*****************************************************\n")

#define H_STRS_SEG_SOCIAL_MENU BLUE( \
"**************************************\n" \
"* -| Menu Tabela Segurança Social |- *\n" \
"*                                    *\n" \
"* 1. Carregar Tabela                 *\n" \
"* 2. Visualizar                      *\n" \
"* 3. Adicionar                       *\n" \
"* 4. Remover                         *\n" \
"* 5. Editar                          *\n" \
"* 6. Guardar                         *\n" \
"* 0. Voltar ao menu anterior         *\n" \
"*                                    *\n" \
"**************************************\n")

#define H_STRS_PROC BLUE( \
"*********************************\n" \
"*  -| Processamento Salarios |- *\n" \
"*                               *\n" \
"*  1. Criar mês                 *\n" \
"*  2. Visualizar                *\n" \
"*  3. Adicionar detalhes        *\n" \
"*  4. Editar detalhes           *\n" \
"*  5. Eliminar detalhes         *\n" \
"*  6. Processar mês             *\n" \
"*  7. Exportar mês para CSV     *\n" \
"*  8. Guardar                   *\n" \
"*  9. Importar mês              *\n" \
"* 10. Apagar mês                *\n" \
"* 0. Voltar ao menu anterior    *\n" \
"*                               *\n" \
"*********************************\n")

#define H_STRS_EMPLOYEES_MENU BLUE( \
"**************************************\n" \
"* -| Menu Gestão de Funcionários |-  *\n" \
"*                                    *\n" \
"* 1. Carregar Tabelas                *\n" \
"* 2. Visualizar                      *\n" \
"* 3. Adicionar                       *\n" \
"* 4. Remover                         *\n" \
"* 5. Editar                          *\n" \
"* 6. Guardar                         *\n" \
"* 0. Voltar ao menu anterior         *\n" \
"*                                    *\n" \
"**************************************\n")

#define H_STRS_REPORTS_MENU BLUE( \
"************************************\n" \
"*          -| Relatórios |-        *\n" \
"*                                  *\n" \
"* 1. Antiguidades dos funcionários *\n" \
"* 2. Estado civil                  *\n" \
"* 3. Bonus                         *\n" \
"* 4. Subsídio Alimentação         *\n" \
"* 5. Porcentagem dos Dependentes   *\n" \
"* 0. Voltar ao menu anterior       *\n" \
"*                                  *\n" \
"************************************\n")

#define H_STRS_IRS_TABLE_HEADER CYAN( \
"*************************************************************\n" \
"* [Linha] | Remuneração     | Numero de Dependentes         *\n" \
"*         | Mensal em €     | 0 | 1 | 2 | 3 | 4 | 5 ou mais *\n" \
"*************************************************************\n")

#define H_STRS_SS_TABLE_HEADER CYAN( \
"*************************************************\n" \
"* [Linha] | Critério | Percentagens de Retenção *\n" \
"*         |          | Empregador  /  Empregado *\n" \
"*************************************************\n")

#define H_STRS_EMPLOYEES_TABLE_HEADER CYAN( \
"*******************************************************************************************************************************************************************\n" \
"* [Linha] | Código      | Primeiro | Último   | Tlf. | Nº Dependentes | Cargo | Estado | Data de    | Data de | Data de | Rendimento | Subsídio de | Nº Titulares *\n" \
"*         | Funcionário | Nome     | Nome     |      |                |       | Cívil  | Nascimento | Entrada | Saída   | Base       | Alimentação |              *\n" \
"*******************************************************************************************************************************************************************\n")

#define H_STRS_PROCESSED_TABLE_HEADER CYAN( \
"*************************************************************************************************************************************************************\n" \
"* [Linha] | Código      | Dias      | Meios | Fins   | Faltas | Salário | Salário  | Retenção | Retenção ISS | Retenção ISS | Bónus     | Salário | Encargo *\n" \
"*         | Funcionário | Completos | Dias  | Semana |        | Bruto   | Ilíquido | IRS      | funcionário  | empregador   | Atribuído | Liquido | Total   *\n" \
"*************************************************************************************************************************************************************\n")

#define H_STRS_PROC_TABLE_HEADER CYAN( \
"****************************************************************\n" \
"* [Linha] | Código      | Dias      | Meios | Fins   | Faltas  *\n" \
"*         | Funcionário | Completos | Dias  | Semana |         *\n" \
"****************************************************************\n")

#endif //STRS_H
