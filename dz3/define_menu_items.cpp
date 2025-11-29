#include <declare_menu_items.hpp>

#include <menu_function.hpp>

const dominator::MenuItem dominator::CARRY = {
    "1 - Керри", 
    "Керри в Dota 2 — это роль героя, который, будучи слабым в начале игры, \n\
становится очень мощным к её концу благодаря накопленным предметам и золоту. \n\
Его основная задача — наносить урон и в конечном итоге «принести» победу команде. \n\
Керри-герои нуждаются в постоянном фарме (убийстве крипов и врагов) для получения \n\
золота и опыта, что делает их зависимыми от поддержки команды в начале игры.",
    dominator::SHOW_DATA,
    &dominator::PLAY
};

const dominator::MenuItem dominator::HARD_SUPPORT = {
    "2 - Hard support", 
    "Hard support — это роль в Dota 2, которая фокусируется на поддержке\n\
союзного керри в ранней игре и обеспечении команды ресурсами, такими как обзор и предметы.\n\
Главная задача хард-саппорта — помочь своему керри комфортно фармить и мешать вражескому \n\
хардлайнеру, при этом не претендуя на золото и опыт в команде.",
    dominator::SHOW_DATA,
    &dominator::PLAY
};

const dominator::MenuItem dominator::BACK_TO_EASY_LINE = {
    "0 - Назад",
    nullptr,
    dominator::BACK,
    &dominator::PLAY
};

namespace {

    const dominator::MenuItem* easy_line_children[] = {
        &dominator::BACK_TO_EASY_LINE,
        &dominator::CARRY,
        &dominator::HARD_SUPPORT
    };

    int easy_line_children_size = sizeof(easy_line_children) / sizeof(easy_line_children[0]);
};

const dominator::MenuItem dominator::MIDER = {
    "1 - Мидер", 
    "Мидер в Dota 2 — это игрок, который занимает центральную линию и является «мозгом»\n\
команды, задавая темп игре. Эта роль требует высокой мобильности,\n\
умения быстро набирать опыт и золото, а также эффективного взаимодействия с союзниками\n\
для создания давления на карте и инициации сражений. Мидеры часто специализируются\n\
на нанесении взрывного магического урона и могут смещаться на другие линии для гангов \n\
уже на ранних этапах игры",
    dominator::SHOW_DATA,
    &dominator::PLAY
};

const dominator::MenuItem dominator::BACK_TO_MID_LINE = {
    "0 - Назад",
    nullptr,
    dominator::BACK,
    &dominator::PLAY
};

namespace {

    const dominator::MenuItem* mid_line_children[] = {
        &dominator::BACK_TO_MID_LINE,
        &dominator::MIDER
    };

    int mid_line_children_size = sizeof(mid_line_children) / sizeof(mid_line_children[0]);
};

const dominator::MenuItem dominator::OFFLANER = {
    "1 - Оффлейнер", 
    "Оффлейнер в Dota 2 — это игрок на 3-й позиции, который идет на самую сложную линию (оффлейн),\n\
чтобы противостоять вражескому керри и его саппортам. Его основная задача — выживать\n\
в трудных условиях, зарабатывать ресурсы, покупать командные предметы и инициировать драки,\n\
а также создавать пространство для других героев команды.",
    dominator::SHOW_DATA,
    &dominator::PLAY
};

const dominator::MenuItem dominator::ROAMER = {
    "2 - Роумер", 
    "Роумер в Dota 2 — это герой или игрок, который не стоит на одной линии,\n\
а постоянно перемещается по карте, чтобы создавать давление на врагов, \n\
помогать союзникам и совершать внезапные атаки (ганки). Эта роль связана \n\
с активностью на ранних стадиях игры, контролем рун и вардов, а также с обеспечением\n\
общей безопасности команды за счет постоянного движения",
    dominator::SHOW_DATA,
    &dominator::PLAY
};

const dominator::MenuItem dominator::BACK_TO_HARD_LINE = {
    "0 - Назад",
    nullptr,
    dominator::BACK,
    &dominator::PLAY
};

namespace {

    const dominator::MenuItem* hard_line_children[] = {
        &dominator::BACK_TO_HARD_LINE,
        &dominator::OFFLANER,
        &dominator::ROAMER
    };

    int hard_line_children_size = sizeof(hard_line_children) / sizeof(hard_line_children[0]);
};


const dominator::MenuItem dominator::EASY_LINE = {
    "1 - Легкая линия",
    "Давай посмотрим какие роли есть на легкой линии",
    dominator::SHOW_CHILDREN,
    &dominator::PLAY,
    easy_line_children,
    easy_line_children_size
};

const dominator::MenuItem dominator::MID_LINE = {
    "2 - Центральная линия",
    "Давай посмотрим какие роли есть на центральной линии",
    dominator::SHOW_CHILDREN,
    &dominator::PLAY,
    mid_line_children,
    mid_line_children_size
};

const dominator::MenuItem dominator::HARD_LINE = {
    "3 - Сложная  линия",
    "Давай посмотрим какие роли есть на сложной линии",
    dominator::SHOW_CHILDREN,
    &dominator::PLAY,
    hard_line_children,
    hard_line_children_size
};

const dominator::MenuItem dominator::LINE_BACK = {
    "0 - Назад",
    nullptr,
    dominator::BACK,
    &dominator::MAIN
};

namespace {

    const dominator::MenuItem* play_children[] = {
        &dominator::LINE_BACK,
        &dominator::EASY_LINE,
        &dominator::MID_LINE,
        &dominator::HARD_LINE
    };

    int play_children_size = sizeof(play_children) / sizeof(play_children[0]);
};

const dominator::MenuItem dominator::PLAY = {
    "1 - Давай посмотрим какие линии есть в доте?",
    "В доте есть 3 линии: ",
    dominator::SHOW_CHILDREN,
    &dominator::MAIN,
    play_children,
    play_children_size
};

const dominator::MenuItem dominator::EXIT = {
    "0 - Я лучше возьму и порешаю Демидовича",
    nullptr,
    dominator::EXIT_PROGRAM,
    &dominator::MAIN
};

namespace {

    const dominator::MenuItem* main_children[] = {
        &dominator::EXIT,
        &dominator::PLAY
    };

    int main_children_size = sizeof(main_children) / sizeof(main_children[0]);
};

const dominator::MenuItem dominator::MAIN = {
    nullptr,
    "Добро пожаловать в кратенький гайд по игре в доту 2",
    dominator::SHOW_CHILDREN,
    nullptr,
    main_children,
    main_children_size
};