const std::string cMenuOptionsText[2][4] = { 
  { "Start Game", "Credits", "Change Language", "Exit"},
  { "Iniciar o Jogo", "Créditos", "Mudar Idioma", "Sair"} };
const std::string cPauseInformation[2][4] = {
  { "Lives: ", "Jump Upgrades: ", "Speed Upgrades: ",
    "Life Upgrades: " },
  { "Vidas: ", "Upgrades de Pulo: ", 
    "Upgrades de Velocidade: ", "Upgrades de Vida: " }
};
const std::string cPauseMenuOptionsText[2][3] = {
  { "Continue", "Return to Main Menu", "Exit"},
  { "Continuar", "Retorna ao Menu", "Sair" }
};

const std::string cPressAnyKey[2] = { "Press Any Key", "Aperte Qualquer Tecla" };
const std::string cInstructions[2] = { "Instructions", "Instruções" };
const std::string cCredits[2] = { "Credits", "Créditos" };
const std::string cThanks[2] = { "Thanks for Playing", "Obrigado por Jogar" };
const std::string cPause[2] = { "Pause Menu", "Menu de Pausa" };
const std::string cExit[2] = { "EXIT", "SAÍDA" };
  
const size_t cGameIntroLines = 12;
const std::string cGameIntroText[2][cGameIntroLines] = {
  {
    "  A boy is walking in a park chasing bugs.",
    "He goes into a cave, while chasing a firefly, and plays inside it for some time.",
    "He trips into a rock and falls in the ground.",
    "When he gets up, he realises that he can't see the entrance.",
    "A little frightened, he walks around looking for an exit, when suddenly",
    "he feels a pressure in his pocket. A bag of sunflower seeds, which he brought",
    "along, was strangely getting bigger and bigger and bigger.",
    "He looks around and suddenly realizes that, actually, he was getting smaller and",
    "smaller and smaller.",
    " - Well, I better find myself an exit, before something worse happens - he says",
    " - thankfully, this cave is naturally illuminated. Otherwise, I would be in",
    " great trouble." 
  }, {
    "  Um garoto está andando pelo parque caçando insetos.",
    "Ele entra numa caversa, enquanto caçava um vagalume, e brinca lá dentro por",
    "um tempo. Ele tropeça numa pedra e cai no chão.",
    "Quando ele levanta, ele percebe que não consegue ver a entrada.",
    "Um pouco assustado, ele anda um pouco procurando por uma saída quando, de",
    "repente, sente uma pressão no seu bolso. Um saco de sementes de girassol, que",
    "ele havia trazido, estava estranhamente crescendo e crescendo e crescendo.",
    "Ele olha ao redor e percebe que, na verdade, ele estava ficando menor e menor",
    "e menor.",
    " - Bem, é melhor eu encontrar uma saída, antes que alguma coisa pior aconteça",
    " - ele diz - ainda bem que esta caverna é iluminada naturalmente. Caso contrário",
    " eu estaria em sérios problemas."
  } };

const size_t cInstructionsLines = 10;
const std::string cInstructionsText[2][cInstructionsLines] = {
  {
    "Move the boy with the arrows left and right",
    "Jump with the arrow up",
    "Throw your seeds at the bugs with the space bar",
    "Pause with ESC or P",
    "Collect upgrades to improve the boy's abilities",
    "      Increase the jump height",
    "      Increase the movement speed",
    "      Increase the life",
    "      Enables double jump",
    "      Enables wall jump"
  }, {
    "Mova o garoto com os direcionais para esquerda e direita",
    "Pule com o direcional para cima",
    "Atire suas sementes nos insetos com a barra de espaço",
    "Pause com ESC ou P",
    "Colete upgrades para melhorar as habilidades do garoto",
    "      Aumenta a altura do pulo",
    "      Aumenta a velocidade de movimento",
    "      Aumenta a vida",
    "      Permite o salto duplo",
    "      Permite o pulo pela parede"
  }
};

const size_t cCreditsLines = 13;
const std::string cCreditsText[2][cCreditsLines] = {
  {
    "Game Design: Abel Soares Siqueira",
    "Game Programming: Abel Soares Siqueira",
    "Game Art:",
    "  Spider: http://openclipart.org/detail/73135/spider-by-redccshirt",
    "  Fly: http://openclipart.org/detail/119407/fly-01-by-anonymous",
    "  Ant: http://openclipart.org/detail/18532/formiga-by-guseinstein",
    "  Music: Cave by Miguel Herrero: http://www.jamendo.com/en/track/224865/cave",
    "",
    "Game developed for the CampJam'12",
    "This game is distributed under the terms of the GNU GPL. Read the README.md and COPYING",
    "You can download this game source at",
    "        https://github.com/abelsiqueira/CampJam2012-BugBoy.git",
    "Special thanks to Kally Chung for all the support and for playing the game"
  }, {
    "Design do Jogo: Abel Soares Siqueira",
    "Programação: Abel Soares Siqueira",
    "Arte:",
    "  Aranha: http://openclipart.org/detail/73135/spider-by-redccshirt",
    "  Mosca: http://openclipart.org/detail/119407/fly-01-by-anonymous",
    "  Formiga: http://openclipart.org/detail/18532/formiga-by-guseinstein",
    "  Música: Cave by Miguel Herrero: http://www.jamendo.com/en/track/224865/cave",
    "",
    "Jogo desenvolvido para o CampJam'12",
    "Este jogo é distribuído sob os termos da GNU GPL. Leia README.md e COPYING",
    "Você pode baixar o código deste jogo em",
    "        https://github.com/abelsiqueira/CampJam2012-BugBoy.git",
    "Agradecimentos especiais à Kally Chung pelo suporte e por jogar"
  }
};

const size_t cGameEndLines = 8;
const std::string cGameEndText[2][cGameEndLines] = {
  {
    "  With his new found powers, the boy finds the way he came from.",
    "As he approaches the cave entrance, the fatigue kicks in. In his",
    "tiny body, this was enough to make him feint...",
    "",
    "  When he wakes up, he is a regular boy again, devoid of any special",
    "powers, but back to his usual size.",
    " - Could I've been dreaming? Is this the real life? Is this just fantasy?",
    " Was my mind playing tr... Oh a dragonfly!"
  }, {
    "  Com seus poderes recém descobertos, o garoto encontra o lugar de onde veio.",
    "Conforme se aproxima da entrada da caverna, a fatiga é demais. Em seu corpo",
    "minúsculo, isso é suficiente para fazê-lo desmaiar...",
    "",
    "  Quando ele acorda, ele é apenas um garoto normal novamente, sem nenhuma poder",
    "especial, mas com seu tamanho usual",
    " - Será que estive apenas sonhando? Esta é a vida real? É apenas fantasia?",
    " Será que minha mente est... Olha, uma libélula!"
  }
};
