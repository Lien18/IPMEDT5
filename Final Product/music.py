if s[0] == "1":
    print('Starting theme song...')
    print s[0]
    pygame.mixer.music.load("JBTheme.mp3")
    pygame.mixer.music.play(-1)
elif s[0] == "2":
    print('shot')
    effect = pygame.mixer.Sound("gunshot.wav")
    effect.play()
elif s[0] == "3":
    print('raceCar')
    effectCar = pygame.mixer.Sound("gt40Engine.wav")
    effectCar.play()
elif s[0] == "4":
    print('stop')
    pygame.mixer.music.stop();
else:
    #print('Press p to start theme song!')
    print s[0]

