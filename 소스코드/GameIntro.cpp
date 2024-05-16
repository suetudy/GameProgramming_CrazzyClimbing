#include "Game.h"
#include "GameIntro.h"

// ���� â ũ��
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// ��� �̹��� ũ��
const int BACKGROUND_WIDTH = 800;
const int BACKGROUND_HEIGHT = 1800;

SDL_Texture* backgroundTexture; // ��� �̹��� �ؽ�ó
int backgroundY; // ��� �̹����� Y ��ǥ


Intro::Intro() {

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
    // intro bgm
    Mix_Music* intro_mus = Mix_LoadMUS("../../Resources/introBgm.mp3");;
    Mix_VolumeMusic(100); // ��� ���� �Ҹ� ����

    Mix_FadeInMusic(intro_mus, -1, 2); // �Ҹ� ������ Ŀ����

    // btn wav
    btn_wav = Mix_LoadWAV("../../Resources/m1/btnSound.wav");

    // Title
    SDL_Surface* bg_surface = IMG_Load("../../Resources/Main_Title.png");
    g_bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
    SDL_FreeSurface(bg_surface);

    g_bg_source_rect.x = 0;
    g_bg_source_rect.y = 0;
    g_bg_source_rect.w = 800;
    g_bg_source_rect.h = 600;

    g_bg_destination_rect.x = 60;
    g_bg_destination_rect.y = 100;
    g_bg_destination_rect.w = 650;
    g_bg_destination_rect.h = 450;

    // ��� �̹��� �ε�
    {
        SDL_Surface* surface = IMG_Load("../../Resources/Mode1_bg.png");
        backgroundTexture = SDL_CreateTextureFromSurface(g_renderer, surface);
        SDL_FreeSurface(surface);
    }

    // ��� �̹��� �ʱ� ��ġ ���� (ȭ�� �Ʒ���)
    backgroundY = 0;




    // Start Button
    SDL_Surface* temp_surface = IMG_Load("../../Resources/Play_Btn_Up.png");
    texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
    SDL_FreeSurface(temp_surface);

    SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
    destination_rectangle_.x = 320;
    destination_rectangle_.y = 450;
    source_rectangle_.x = 0;
    source_rectangle_.y = 0;

    destination_rectangle_.w = 150;
    destination_rectangle_.h = 80;

}

Intro::~Intro() {
    SDL_DestroyTexture(g_bg_texture);
    SDL_DestroyTexture(texture_);
    Mix_FreeMusic(intro_mus);
    Mix_FreeChunk(btn_wav);
}

void Intro::Update()
{
    // ��� �̹��� �̵�
    //if (c = true) {
    //   backgroundY -= 7; // ���ϴ� �ӵ��� ����
    //   c = false;
    //}

    backgroundY -= 7;

    // ��� �̹����� ȭ�� ���� ����� ������ ��� �̵�
    if (backgroundY <= -BACKGROUND_HEIGHT + WINDOW_HEIGHT) {
        backgroundY = -BACKGROUND_HEIGHT + WINDOW_HEIGHT;
    }
}

void Intro::Render() {

    // ��� �̹��� �׸���
    SDL_Rect backgroundRect = { 0, backgroundY, BACKGROUND_WIDTH, BACKGROUND_HEIGHT };
    SDL_RenderCopy(g_renderer, backgroundTexture, NULL, &backgroundRect);

    //Main_Title
    SDL_RenderCopy(g_renderer, g_bg_texture, &g_bg_source_rect, &g_bg_destination_rect);

    // Start Button
    SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);

    SDL_RenderPresent(g_renderer);

}

void Intro::HandleEvents() {

    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            g_flag_running = false;
            break;

        case SDL_MOUSEBUTTONDOWN:

            // If the mouse left button is pressed. 
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                if (mouseX >= destination_rectangle_.x && mouseX < destination_rectangle_.x + destination_rectangle_.w
                    && mouseY >= destination_rectangle_.y && mouseY < destination_rectangle_.y + destination_rectangle_.h) {
                    g_current_game_phase = PHASE_HOME;
                    Mix_PlayChannel(-1, btn_wav, 0);
                }

            }
            break;

        default:
            break;
        }
    }

}