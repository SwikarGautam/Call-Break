#include "Score.hpp"
#include <bits/stdc++.h>
#include <sstream>

//  Score window
int Score::showScoreWin(std::vector<Player> players, int currentRound){
    sf::RenderWindow SCORE_WINDOW;

    SCORE_WINDOW.create(sf::VideoMode(SCORE_WIDTH, SCORE_HEIGHT), "Score", sf::Style::None);
    SCORE_WINDOW.setFramerateLimit(30);

    		// Load texture for background image and load img
	sf::Texture texture;
	if (!texture.loadFromFile("src/Images/woodBack.png"))
	{
		std::cout << "Error loading score window background image.";
	}
	// if (!texture.loadFromFile("src/Images/scoreBackground.jpg"))
	// {
	// 	std::cout << "Error loading score window background image.";
	// }
	sf::Sprite scoreBackground(texture);
	// scoreBackground.scale(sf::Vector2f(0.4, 0.4));


    while (SCORE_WINDOW.isOpen())
    {
		sf::Event event;

        Text text[4];
    
        // text[0].loadText("0/0", GAME_WIDTH/2, GAME_HEIGHT - 200);
        // text[1].loadText("0/0", 41, GAME_HEIGHT/2 - 20);
        // text[2].loadText("0/0", GAME_WIDTH/2,  100);
        // text[3].loadText("0/0", GAME_WIDTH - 70, GAME_HEIGHT/2 - 20);
        std::ostringstream ss;


		while (SCORE_WINDOW.pollEvent(event))
		{
				if (event.type == sf::Event::Closed)
				{
					SCORE_WINDOW.close();
				}
                if (event.type == sf::Event::KeyPressed)
                {
				    //	Esc  key pressed
                    if (event.key.code == sf::Keyboard::Enter)
                    {
					    //	Escape key pressed closes credits window
                        SCORE_WINDOW.close();
                    }
                }
    
        }
        Text headText;
        Text titleText;
        Text text1[6][5];
        float total_scores[4] = {0,0,0,0};
        Text infoText;
        float initX = 50;
        float initY = 40;

        titleText.loadText("", initX - 40, initY - 35, 20, sf::Color::Black, true);
        headText.loadText("", initX, initY, 18, sf::Color::Black, false);
        


        //  Info text
        infoText.loadText("", SCORE_WIDTH/2 - 75, SCORE_HEIGHT - 25, 18, sf::Color::Black, true);
        for (int i=0; i<=currentRound; ++i)
        {
            initY = float(50 + (i+1) * 40);
            for (int j = 0; j<=4; ++j)
            {
            text1[i][j].loadText("", initX + 95 * (j), initY, 18, sf::Color::Black, false);
            }
        }

        for (int j = 0; j<=4; ++j)
            {
            text1[5][j].loadText("", initX + 95 * (j), initY+50, 18, sf::Color::Black, false);
            }
        
        SCORE_WINDOW.clear();
        SCORE_WINDOW.draw(scoreBackground);


        ss<<"\t\t\t\t\tScores";
        titleText.setText(ss.str());
        ss.str("");

        ss<<"S.N\t\t You\t\tBot-I\t\tBot-II\t\tBot-III";
        headText.setText(ss.str());
        ss.str("");

        ss<<"press enter key to continue";
        infoText.setText(ss.str());
        ss.str("");
        // ss<<players[1].round_score;
        for (int round = 0; round <=currentRound; ++round) 
        {

        for (int i = 0; i<4; ++i)
        {
            ss.str("");
            if (i == 0)
                ss<<"  " <<round + 1 << ".\t\t\t" << players[i].scores[round];
            else
                ss<< "\t\t\t" << players[i].scores[round];

            text1[round][i].setText(ss.str());
            total_scores[i] += players[i].scores[round];
        }
        }


        for (int i = 0; i<4; ++i)
        {
            ss.str("");
            if (i == 0)
                ss<<"Total\t\t" << total_scores[i];
            else
                ss<< "\t\t\t" << total_scores[i];

            text1[5][i].setText(ss.str());
        }
        
        headText.renderText(SCORE_WINDOW);
        titleText.renderText(SCORE_WINDOW);
        for (int i=0 ; i<=5; i++)
        {
        for (int j = 0; j<5; j++) 
        {
            text1[i][j].renderText(SCORE_WINDOW);
        }
        }
        infoText.renderText(SCORE_WINDOW);
        SCORE_WINDOW.display();
    }
    return -1;
}