#ifndef DEFAULTCONFIG_H
#define DEFAULTCONFIG_H
#include <string>

//configwindow

static const std::string g_tab1 = "Dane";
static const std::string g_tab2 = "Algorytm";
static const std::string g_tab3 = "Lista Tabu";

static const std::string g_button1 = "Cancel";
static const std::string g_button2 = "OK";

//configtab1

static const std::string g_width_name = "Szerokość";
static const std::string g_height_name = "Wysokość";
static const std::string g_size_name = "Rozmiar figury";

static const int g_width = 100;
static const int g_height = 200;
static const int g_size = 20;

//configtab2

static const std::string g_iteration_count_name = "Ilość iteracji";
static const std::string g_change_count_name = "Wiekość sąsiedztwa: ";

static const int g_iteration_count = 50;
static const int g_change_count = 5;

//configtab3

static const std::string g_tabu_list_size_name = "Długość listy Tabu";
static const std::string g_tabu_list_time_name = "Czas pobytu na Liście Tabu";

static const int g_tabu_list_size = 20;
static const int g_tabu_list_time = 10;


#endif // DEFAULTCONFIG_H
