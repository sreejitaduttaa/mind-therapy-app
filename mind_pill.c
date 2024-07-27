#include<stdio.h>
#include<ctype.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct dmood{
    int day;
    int mon;
    int yr;
    int wday;
    char mood[8];
}; 
struct user{
    char pass[20];
    char username[20];
    char fname[20];
    char lname[20];
};
struct wdays{
    char day[10];
    } days[] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"} ;
struct mon{
    char mname[10];
}month[]={"January","February","March","April","May","June","July","August","September","October","November","December"};
struct todo
{
    int day;
    int mon;
    int yr;
    char content[200];
};
struct user userinfo;
struct quotes{
    char line[80];
};
struct questions{
    char q[100];
}ques[]={"What was the best thing that happened to you today?", 
"What steps did you take today towards a goal you're working on?",
"What is something that made you laugh today?", 
"Who made your day better today? How can you pay that feeling forward?",
"What made today unique?",
"What is one thing you want to remember from today?",
"When did you feel most authentically yourself today?",
"How can you make tomorrow (even) better than today?",
"What do you owe yourself?"
};

char username[20];
int c;
void signup();
void login();
int menu();
void frontpage();
void monthmood();
void homepage();
void recommended();
void relax(char c);
void phys(char n);
void relaxation();
void physical();
void fassist();
void focus();
void meditation();
void timer(int x, int y,int h, int m, int s);
void goals();
void journal();
int moodsearch(int d, int m,int y, int w);
int dailymoodtracker();
void reflect();
int dmood_check(char ch);
void exitpage();
void exitif(char n);
void darktheme();
void quote();
void headerdesign();
void gotoxy(int ,int);

void main(){
    system("cls");
    switch (menu())
        {
        case 115:  // ASCII for s
            signup();
            break;
        
        case 108:  // ASCII for l
            login();
            break;

        case 101:// ASCII for e
            exitpage();
            break;

        default:
            menu();
        }    
}
void frontpage(){
    char x='z';
    time_t secs= time(NULL);
    struct tm t = *localtime(&secs);
    system("cls"); system("color 10");
    gotoxy(150,1); puts("Exit[E]");
    headerdesign();
    if(4<=t.tm_hour && t.tm_hour<12){gotoxy(45,9);  printf("Good Morning, %s ^_^", userinfo.fname);}
    else if(12<=t.tm_hour && t.tm_hour<17){gotoxy(45,9); printf("Good Afternoon, %s ^_^",userinfo.fname);}
    else if(17<=t.tm_hour && t.tm_hour<21){gotoxy(45,9); printf("Good Evening, %s ^_^",userinfo.fname);}
    else if(21<=t.tm_hour && t.tm_hour <=23 || 0<=t.tm_hour && t.tm_hour <4  ){gotoxy(45,9); printf("Good night, %s ^_^",userinfo.fname);}
    gotoxy(45,11); puts("Check in with yourself, then pick a tuned");
    gotoxy(45,12); puts("mindfulness session to improve your day! (*^_^*)");
    gotoxy(66,20); puts("Press any key to GET STARTED!!");
    gotoxy(98,20); c=getch();
    if(c==69||c==101){exitpage();}
    if(dmood_check(x)!=0) dailymoodtracker();
    else homepage();
}
void homepage(){
    int x=1;
    time_t secs= time(NULL);
    struct tm t = *localtime(&secs);
    system("cls"); system("color 10");
    gotoxy(150,1); puts("Exit[E]");
    headerdesign(); 
    gotoxy(65,3); quote();

    gotoxy(20,5); puts("::: Weekly Mood Log :::");
    for(int i=t.tm_wday;i>=0;i--){
        secs=secs- (86400*i);
        struct tm t = *localtime(&secs); // to find out dates of previous days in the week
        gotoxy(x,7); printf("|%.3s", days[t.tm_wday].day);
        gotoxy(x,8); moodsearch(t.tm_mday,t.tm_mon+1,t.tm_year+1900,t.tm_wday);
        x+=8;
        secs= time(NULL);
    } 
    gotoxy(6,10);puts("Press [Y] to view last 30 days mood insight ");
    gotoxy(13,11);puts("and any other key to skip!");

    for(int i=5;i<=50;i++){gotoxy(i,13);putch('-');}

    gotoxy(20,15); puts("::: Goal of the Day :::");
    gotoxy(4,17); puts("Start with small tasks to reach the big dreams!");
    gotoxy(23,18); printf("%s, %.3s %d", days[t.tm_wday].day , month[t.tm_mon].mname,t.tm_mday);

    gotoxy(70,5); puts("::: Journal :::");
    gotoxy(64,7);puts("A personal journal is an ideal ");
    gotoxy(63,8); puts("environment in which to \"become\".");
    gotoxy(60,9);puts("It is a perfect place for you to think, ");
    gotoxy(58,10); puts("feel, discover, expand, remember, and dream.");
    gotoxy(58,12); puts("Press [Y] to journal and any other key to skip!");

    for(int i=57;i<=105;i++){gotoxy(i,13);putch('-');}
    
    gotoxy(70,15); puts("::: Self Reflection :::");
    gotoxy(57,17);puts("Hit the pause button on your busy life and reflect ");
    gotoxy(57,18); puts("on the past 24 hours with these questions that will");
    gotoxy(57,19);puts("give you ample motivation to get the words flowing.  ");
    gotoxy(58,21); puts("Press [Y] to reflect and any other key to skip!");

    gotoxy(116,5); puts("::: Recommended Activities :::");
    gotoxy(120,7);puts("Build emotional strength ");
    gotoxy(120,8); puts("by practicing relaxation ");
    gotoxy(120,9);puts("and physical activities.");
    gotoxy(110,11); puts("Press [Y] to continue and any other key to skip!");

    for(int i=111;i<=154;i++){gotoxy(i,13);putch('-');}

    gotoxy(122,15); puts("::: Relax Yourself :::");
    gotoxy(123,17);puts("Simple way for your ");
    gotoxy(124,18); puts("mental well being");
    gotoxy(112,21); puts("Press [Y] to relax and any other key to skip!");
    
    goals();
    
}
void goals(){
    char choice,content[200];
    int flag=0;
    time_t secs= time(NULL);
    struct tm t = *localtime(&secs);
    FILE* fgoal;
    char userdgoal[50];
    gotoxy(150,1); puts("Exit[E]");
    strcpy(userdgoal,username);
    strcat(userdgoal,"_goal.dat");
    fgoal=fopen(userdgoal,"ab+"); 
    struct todo utodo;
    while(fread(&utodo, sizeof(utodo), 1, fgoal)>0 && flag==0){
        if(t.tm_mday==utodo.day && t.tm_mon+1==utodo.mon && t.tm_year+1900==utodo.yr){
            flag=1;  
            gotoxy(2,20); puts(utodo.content);            
        }     
    }         
    if(flag==0) {
        gotoxy(7,20);puts("+Press [A] to add a goal for the day"); 
        gotoxy(12,21);puts("and any other key to skip!"); 
    }
    gotoxy(48,11); c = getch(); exitif(c);
    if(c==80||c==121) monthmood();

    if(flag==0){gotoxy(48,21); choice=getch();} exitif(choice);
    if(choice==65||choice==97){ 
            fflush(stdin);
            gotoxy(2,22);puts("Please write down your goal for the day-");
            gotoxy(2,23);gets(content);
            fflush(stdin);
            struct todo utodo={t.tm_mday,t.tm_mon+1,t.tm_year+1900,""};
            strncpy(utodo.content,content,49); 
            fwrite(&utodo,sizeof(utodo),1,fgoal);
    }
    fclose(fgoal);

    gotoxy(105,12); c= getch(); exitif(c);
    if(c==89||c==121){journal();}

    gotoxy(105,21); c= getch(); exitif(c);
    if(c==89||c==121){reflect();}

    gotoxy(158,11); c= getch(); exitif(c);
    if(c==89||c==121){recommended();}

    gotoxy(157,21); c= getch(); exitif(c);
    if(c==89||c==121){fassist();}

    darktheme();
    gotoxy(63,5);printf("We hope you had a good time here, %s!",userinfo.fname);
    gotoxy(69,7);puts("Have a good rest of your day!");
    gotoxy(70,8);puts("Hope to see you soon again!");
    gotoxy(73,10);puts("Press [B] to go back");
    gotoxy(70,12);puts("And any other key to exit!");
    gotoxy(98,12);c=getch();
    if(c==66||c==98){homepage();}
    else{exitpage();}

}  
void fassist(){
    char n;
    system("cls"); system("color 17"); headerdesign();
    gotoxy(150,1); puts("Exit[E]");
    gotoxy(70,4); puts("::: Focus Assist :::");

    gotoxy(10,10); puts("[A] Meditation Session");
    gotoxy(10,12); puts("Meditation can give you a sense of calm, peace and");
    gotoxy(10,13); puts("balance that can benefit both your emotional well-being ");
    gotoxy(10,14); puts("and your overall health. You can also use it to relax and ");
    gotoxy(10,15); puts("cope with stress by refocusing your attention on something calming. ");
    gotoxy(10,16); puts("Meditation can help you learn to stay centered and keep inner peace.");

    gotoxy(85,10); puts("[B] Mindful Focus Session");
    gotoxy(85,12); puts("Focusing can help people become reacquainted with internal ");
    gotoxy(85,13); puts("awareness of their emotions, helping them become better able");
    gotoxy(85,14); puts("to more readily address them. It can encourage a person if they ");
    gotoxy(85,15); puts("wish to go and explore a feeling or movement more deeply.This deepens");
    gotoxy(85,16); puts("the bond, taking the therapeutic connection to a new relational depth.");

    gotoxy(69,21); printf("Enter [P] to go back  ");
    gotoxy(68,19); printf("Enter [A/B] to continue  ");
    n=getch(); exitif(n);
    if (n==65||n==97){meditation();}
    else if(n==66||n==98){focus();}
    else if(n==80||n==112){homepage();}
    else{
        gotoxy(60,21);printf("Invalid choice! Press any key to select again!"); 
        getch();fassist();
    }
}
void meditation(){
    int h,m,s;
    char c;
    
    darktheme();
    gotoxy(150,1); puts("Exit[E]");
    gotoxy(68,4); puts("=== Meditation Session ===");
    
    gotoxy(10,6); puts("It'll will help you control anxiety and stress, and ");
    gotoxy(10,7); puts("increase your attention span by working on self-awareness.");
    gotoxy(10,9); puts("1. Sit or lie comfortably and close your eyes.");
    gotoxy(10,11); puts("2. Focus on your breath. Don't control it, just ");
    gotoxy(10,12); puts("observe each moment. For example, notice how your");
    gotoxy(10,13); puts("stomach feels or where it moves during inhalation ");
    gotoxy(10,14); puts("or feel the air moving through your nose.");
    gotoxy(10,16); puts("3. If you notice your attention drift away and you're");
    gotoxy(10,17); puts("thinking about something else, just gently return to");
    gotoxy(10,18); puts("noticing your breath. And, don't worry about that-it's");
    gotoxy(10,19); puts("completely normal. Each time you return your focus to the ");
    gotoxy(10,20); puts("breath, you're exercising your focus - like a muscle. The");
    gotoxy(10,21); puts("more you train, the stronger - the more mindful - you grow.");

    
    gotoxy(100,6);puts("Press [C] to start the activity with a timer");
    gotoxy(110,8);puts("Press [B] to go back");
    gotoxy(140,8); c=getch(); exitif(c);
    if(c==67||c==99){
        gotoxy(93,11);printf("Please enter your timer range[HH:MM:SS](using space): ");
        scanf("%d%d%d",&h,&m,&s);
        timer(120,14,h,m,s);
        gotoxy(100,16);puts("Congratulations! You've completed the activity!");
        gotoxy(110,18);puts("Press any key to go back!");
        gotoxy(140,18); getch();fassist();
    }
    else if(c==66 || c==98){fassist();}
    else{
        gotoxy(100,10);printf("Invalid choice! Press any key to select again!"); 
        getch();meditation();
    }

}
void focus(){
    int h,m,s;
    char c;

    darktheme();
    gotoxy(150,1); puts("Exit[E]");
    gotoxy(66,4); puts("=== Mindful Focus Session ===");
    gotoxy(10,6); puts("1. Close your eyes, relax, and sit upright.");
    gotoxy(10,8); puts("2. Place your full focus on your breath. Simply maintain ");
    gotoxy(10,9); puts("an ongoing flow of attention on the experience of your");
    gotoxy(10,10); puts("breathing: inhale, exhale, inhale, exhale. To help your ");
    gotoxy(10,11); puts("focus stay on your breathing, count silently at each exhalation.");
    gotoxy(10,13); puts("3. Any time you find your mind distracted, simply release the");
    gotoxy(10,14); puts("distraction by returning your focus to your breath. Most important,");
    gotoxy(10,15); puts("allow yourself to enjoy these minutes. Throughout the rest of the");
    gotoxy(10,16); puts("day, other people and competing urgencies will fight for your ");
    gotoxy(10,17); puts("attention. But for these few minutes, your attention is all your own.");
    gotoxy(10,19); puts("Once you finish this practice and get ready to start working, ");
    gotoxy(10,20); puts("mindfulness can help increase your effectiveness.");
    
    gotoxy(100,6);puts("Press [C] to start the activity with a timer");
    gotoxy(110,8);puts("Press [B] to go back");
    gotoxy(140,8); c=getch(); exitif(c);
    if(c==67||c==99){
        gotoxy(93,11);printf("Please enter your timer range[HH:MM:SS](using space): ");
        scanf("%d%d%d",&h,&m,&s);
        timer(120,14,h,m,s);
        gotoxy(100,16);puts("Congratulations! You've completed the activity!");
        gotoxy(110,18);puts("Press any key to go back!");
        gotoxy(140,18); getch();fassist();
    }
    else if(c==66 || c==98){fassist();}
    else{
        gotoxy(100,10);printf("Invalid choice! Press any key to select again!"); 
        getch();focus();
    }
}
void recommended(){
    char n;
    system("cls"); system("color 17"); headerdesign();
    gotoxy(150,1); puts("Exit[E]");
    gotoxy(70,4); puts("::: Recommended Activities :::");
    gotoxy(58,6); puts("Exercise increases your overall health and your sense of");
    gotoxy(59,7); puts("well-being, which puts more pep in your step every day.");
    gotoxy(28,10); puts("[A] Relaxation Activities");
    gotoxy(10,12); puts("When faced with many responsibilities and tasks or the demands of ");
    gotoxy(9,13); puts("an illness,relaxation techniques may not be a priority in your life.");
    gotoxy(8,14); puts("But that means you might miss out on the health benefits of relaxation.");
    gotoxy(110,10); puts("[B] Physical Activities");
    gotoxy(98,12); puts("Physical exercise can play an important role in  ");
    gotoxy(97,13); puts("mental well-being and can even relieve symptoms of");
    gotoxy(96,14); puts("mental health conditions like depression and anxiety.");
    gotoxy(69,20); printf("Enter [P] to go back  ");
    gotoxy(68,18); printf("Enter [A/B] to continue  ");
    n=getch(); exitif(n);
    if (n==65||n==97){relaxation();}
    else if(n==66||n==98){physical();}
    else if(n==80||n==112){homepage();}
    else{exit(0);}
}
void relaxation(){
    char c;
    system("cls"); system("color 17"); headerdesign();
    gotoxy(70,4); puts("::: Relaxation Activities :::");
    gotoxy(58,6); puts("Practicing relaxation techniques can have many benefits.");
    gotoxy(57,7); puts("It helps us to have a calmer and clearer mind which aids");
    gotoxy(56,8); puts("positive thinking, concentration, memory and decision making.");
    gotoxy(5,11); puts("[A] Deep Breathing");
    gotoxy(5,13); puts("Deliberately copying a relaxed");
    gotoxy(5,14); puts("breathing pattern seems to calm ");
    gotoxy(5,15); puts("the nervous system that controls");
    gotoxy(5,16); puts("the body's involuntary functions.");
    gotoxy(45,11); puts("[B] Guided Imagery");
    gotoxy(45,13); puts("Guided imagery helps you use your");
    gotoxy(45,14); puts("imagination to take you to ");
    gotoxy(45,15); puts("a calm, peaceful place.");
    gotoxy(85,11); puts("[C] Progressive Muscle Relaxation");
    gotoxy(85,13); puts("PMR is a type of relaxation   ");
    gotoxy(85,14); puts("technique that can help reduce");
    gotoxy(85,15); puts("the symptoms of stress.");
    gotoxy(125,11); puts("[D] Autogenic relaxation");
    gotoxy(125,13); puts("In this relaxation technique,");
    gotoxy(125,14); puts("you use both visual imagery and");
    gotoxy(125,15); puts ("body awareness to reduce stress.");
    gotoxy(5,18); puts("[E] Mindful Walking");
    gotoxy(5,19); puts("Mindful walking can help us be");
    gotoxy(5,20); puts("present in the moment and focus");
    gotoxy(5,21); puts("on the happenings around us.");
    gotoxy(45,18); puts("[F] Cognitive Defusion");
    gotoxy(45,19); puts("It involves creating space between ");
    gotoxy(45,20); puts("ourselves and our thoughts and ");
    gotoxy(45,21); puts("feelings so that they have");
    gotoxy(45,22); puts("less of a hold over us.");
    gotoxy(85,18); puts("[G] Self Compassion Pause");
    gotoxy(85,19); puts("It yields a number of benefits, ");
    gotoxy(85,20); puts("including lower levels of");
    gotoxy(85,21); puts("anxiety and depression.");
    gotoxy(125,18); puts("[H] Beach Visualisation");
    gotoxy(125,19); puts("Beach scenes are a popular");
    gotoxy(125,20); puts("visualization due to their ");
    gotoxy(125,21); puts("calming and tranquil impact.");
    gotoxy(67,24); printf("Enter your choice to continue");
    gotoxy(71,26); printf("Enter [P] to go back        ");
    c=getch();
    c=tolower(c);
    if(c=='a'||c=='b' ||c=='c'||c=='d'||c=='e'||c=='f'||c=='g'||c=='h'){relax(c);}
    else if(c==80 || c==112){recommended();}
    else{
        gotoxy(60,24);printf("Invalid choice! Press any key to select again!"); 
        getch(); relaxation();}
}
void physical(){
    char c;
    system("cls"); system("color 17"); headerdesign();
    gotoxy(70,4); puts("::: Physical Activities :::");
    gotoxy(58,6); puts("Physical activity is not only good for your body,");
    gotoxy(67,7); puts("but it's also great for your mind.");

    gotoxy(5,11); puts("[A] Walking");
    gotoxy(5,13); puts("A brief walk outside can");
    gotoxy(5,14); puts("rejuvenate or freshen the mind.");

    gotoxy(45,11); puts("[B] Climbing Stairs");
    gotoxy(45,13); puts("Climbing stairs can help your");
    gotoxy(45,14); puts("body release endorphins that");
    gotoxy(45,15); puts("ensure you feel strong and good.");
   
    gotoxy(85,11); puts("[C] Running");
    gotoxy(85,13); puts("Running can control stress and");
    gotoxy(85,14); puts("boost the body's ability to deal");
    gotoxy(85,15); puts("with existing mental tension.");

    gotoxy(125,11); puts("[D] Cycling");
    gotoxy(125,13); puts("Cycling helps keep people happier");
    gotoxy(125,14); puts("by promoting a healthy, positive");
    gotoxy(125,15); puts ("shift in mental wellbeing.");

    gotoxy(67,19); puts("Enter your choice to continue");
    gotoxy(71,21); printf("Enter [P] to go back         ");
    c=getch();
    c=tolower(c); 
    if(c=='a'||c=='b' ||c=='c'||c=='s'){ phys(c); }
    else if(c==80 || c==112){recommended();}
    else{
        gotoxy(60,24);printf("Invalid choice! Press any key to select again!"); 
        getch();physical();}

}
void relax(char n){
    darktheme();
    char c;
    int h,m,s;
    gotoxy(67,3); puts("=== Relaxation Activities ===");
    if(n=='a'){
        gotoxy(70,5); puts("::: Deep Breathing :::");
        gotoxy(60,7); puts("Practicing breathing exercises and mindfulness ");
        gotoxy(60,8); puts("can lead to better mental health and positive ");
        gotoxy(60,9); puts("emotions, and alleviate stress and depression.");
    }
    else if(n=='b'){
        gotoxy(70,5); puts("::: Guided Imagery :::");
        gotoxy(55,7); puts("You can use it to promote relaxation, which can lower ");
        gotoxy(52,8); puts("blood pressure and reduce other problems related to stress. ");
        gotoxy(46,9); puts("You can also use it to help reach goals, manage pain and promote healing.");
    }
    else if(n=='c'){
        gotoxy(63,5); puts("::: Progressive Muscle Relaxation :::");
        gotoxy(52,7); puts("PMR relieves tension, stress, anxiety, and pain throughout your ");
        gotoxy(50,8); puts("entire body while simultaneously calming your mind and directing your");
        gotoxy(47,9); puts("attention away from problems and onto the feeling of relaxing and letting go.");
    }
    else if(n=='d'){
        gotoxy(68,5); puts("::: Autogenic relaxation :::");
        gotoxy(60,7); puts("You repeat words or suggestions in your mind ");
        gotoxy(58,8); puts("that may help you relax and reduce muscle tension.");
    }
    else if(n=='e'){
        gotoxy(70,5); puts("::: Mindful Walking :::");
        gotoxy(64,7); puts("Mindful walking simply means walking");
        gotoxy(58,8); puts("while being aware of each step and of our breath.");
    }
    else if(n=='f'){
        gotoxy(68,5); puts("::: Cognitive Defusion :::");
        gotoxy(53,7); puts("Defusion involves distancing, disconnecting or seeing thoughts ");
        gotoxy(55,8); puts("and feelings for what they are not what they say they are.");
        gotoxy(70,9); puts("STOP, STEP BACK, OBSERVE");
    }
    else if(n=='g'){
        gotoxy(67,5); puts("::: Self Compassion Pause :::");
        gotoxy(50,7); puts("Self-compassion describes a positive and caring attitude of a person ");
        gotoxy(46,8); puts("toward her- or himself in the face of failures and individual shortcomings.");
        gotoxy(48,9); puts("As a result of this caring attitude, individuals high in self-compassion");
        gotoxy(56,10); puts("are assumed to experience higher individual well-being.");
    }
    else if(n=='h'){
        gotoxy(68,5); puts("::: Beach Visualisation :::");
        gotoxy(52,7); puts("Looking at an image of the sea can bring us many of the same");
        gotoxy(51,8); puts("wellbeing benefits of being in and around water. It can reduce ");
        gotoxy(57,9); puts("our anxiety and pain, and soothe our nervous system.");
    }
    gotoxy(63,12);puts("Press [C] to start the activity with a timer");
    gotoxy(73,14);puts("Press [B] to go back");
    gotoxy(95,14); c=getch();
    if(c==67||c==99){
        gotoxy(55,16);printf("Please enter your timer range[HH:MM:SS](using space): ");
        gotoxy(110,16); scanf("%d%d%d",&h,&m,&s);
        timer(80,18,h,m,s);
        gotoxy(61,20);puts("Congratulations! You've completed the activity!");
        gotoxy(71,22);printf("Press any key to go back!                     ");
        getch();relaxation();
    }
    else if(c==66 || c==98){relaxation();}
    else{
        gotoxy(60,24);printf("Invalid choice! Press any key to select again!"); 
        getch();relax(n);
        }

}
void phys(char n){
    
    darktheme();
    gotoxy(70,3); puts("=== Physical Activities ===");
    char c;
    int h=0,m=0,s=0; 
    if(n=='a'){
        gotoxy(75,5); puts("::: Walking :::");
        gotoxy(55,7); puts("Walking helps boost your mood because it increases blood");
        gotoxy(59,8); puts("flow and blood circulation to the brain and body.");
    }
    else if(n=='b'){
        gotoxy(72,5); puts("::: Climbing Stairs :::");
        gotoxy(61,7); puts("As you climb stairs your body releases endorphins,");
        gotoxy(62,8); puts("which are \"feel-good\" brain chemicals that boost");
        gotoxy(66,9); puts("your mood and reduce your stress levels.");
    }
    else if(n=='c'){
        gotoxy(76,5); puts("::: Running :::");
        gotoxy(56,7); puts("Running outside could have benefits, like lessening feelings");
        gotoxy(60,8); puts("of loneliness and isolation, reducing the effects of");
        gotoxy(62,9); puts("stress, and helping with depression and anxiety.");
    }
    else if(n=='d'){
        gotoxy(76,5); puts("::: Cycling :::");
        gotoxy(55,7); puts("Cycling and walking both release our 'feel-good' hormones");
        gotoxy(61,8); puts("known as endorphins. These hormones help to");
        gotoxy(62,9); puts("relax your mind and make you feel happier.");
    }
    gotoxy(63,12);puts("Press [C] to start the activity with a timer");
    gotoxy(73,14);puts("Press [B] to go back");
    gotoxy(95,14); c=getch();
    if(c==67||c==99){
        gotoxy(55,16);printf("Please enter your timer range[HH:MM:SS](using space): ");
        scanf("%d%d%d",&h,&m,&s);
        timer(80,18,h,m,s);
        gotoxy(61,20);puts("Congratulations! You've completed the activity!");
        gotoxy(71,22);printf("Press any key to go back!                      ");
        getch(); physical();
    }
    else if(c==66 || c==98){physical();}
    else{ 
        gotoxy(60,24);printf("Invalid choice! Press any key to select again!"); 
        getch();phys(n);
    }
}
void reflect(){
     char c,ch,con[200];
    time_t secs= time(NULL);
    struct tm t= *localtime(&secs);
    system("cls"); system("color 17");  headerdesign();
    gotoxy(150,1); puts("Exit[E]");
    gotoxy(66,4); puts("::: Daily Self Reflection :::");
    gotoxy(53,8); puts("Exploring your values, opinions, and personality traits");
    gotoxy(51,9); puts("in writing can teach you more about who you are as a person.");
    gotoxy(49,10); puts("This in-depth reflection can strengthen not just the relationship");
    gotoxy(46,11); puts("you have with yourself, but also the connections you build with others.");
    gotoxy(68,17); puts("Press [C] to GET STARTED!");
    gotoxy(70,18); printf("Press [B] to go BACK");
    gotoxy(94,18); c = getch(); exitif(c);
    if(c==67 || c==99){// ASCII FOR C
        for(int i=0;i<=9;i++){
            darktheme();
            gotoxy(70,4); puts("::: Daily Reflection :::");
            gotoxy(74,6); printf("%s, %.3s %d", days[t.tm_wday].day , month[t.tm_mon].mname,t.tm_mday);
            gotoxy(5,9); puts("<");
            gotoxy(150,9); puts(">");
            fflush(stdin);
            gotoxy(20 ,8); puts(ques[i].q);
            gotoxy(20 ,10); puts("Answer:");
            gotoxy(30 ,10); gets(con);
            fflush(stdin);
            printf("\n\n\n\t\t\t\t\t\t\t\t     Press any key to continue  "); 
            printf("\n\t\t\t\t\t\t\t\t       Press [B] to go back ");  
            printf("\n\n\t\t\t\t\t\t\t\t     Enter you choice- "); 
            ch=getch(); 
            if(ch==66||ch==98){ homepage(); break;}
        } 
    }
    else if(c==66||c==98){homepage();} //ASCII FOR B
    else{
        gotoxy(53,19);puts("You entered an invalid choice, press any key to give input again!");
        getch(); reflect();
    }
}
void journal(){ 
    char tit[2],con[2];
    time_t secs= time(NULL);
    struct tm t= *localtime(&secs);
    system("cls"); headerdesign();
    gotoxy(150,1); puts("Exit[E]");
    gotoxy(70,4); puts("::: Daily Journal :::");
    gotoxy(44,7); puts("Journaling can help you manage anxiety, reduce stress and cope with depression.");
    gotoxy(49,8); puts("Journaling helps control your symptoms and improve your mood by ");
    gotoxy(51,9); puts("helping you prioritize problems, fears and concerns, ");
    gotoxy(34,10); puts("tracking any symptoms day-to-day so that you can recognize triggers and learn ways to better control them, ");
    gotoxy(36,11);  puts("and providing an opportunity for positive self-talk and identifying negative thoughts and behaviours.");
    gotoxy(68,16); puts("Press [C] to GET STARTED");
    gotoxy(70,17); puts("Press [B] to go BACK");
    gotoxy(94,17); c = getch(); exitif(c);
    if(c==67 || c==99){// ASCII FOR C
        darktheme();
        gotoxy(70,4); puts("::: Safe Space :::");
        fflush(stdin);
        gotoxy(69,6); puts("=== Your Free Thoughts ===");
        gotoxy(74,7); printf("%s, %.3s %d", days[t.tm_wday].day , month[t.tm_mon].mname,t.tm_mday);
        gotoxy(0,9); puts("Title:");
        gotoxy(0,10); puts("Notes:");
        system("color 02");
        gotoxy(7,9); fflush(stdin); gets(tit);
        gotoxy(0,11); fflush(stdin); gets(con);
        printf("\n\n\n\t\t\t\t\t\t\t\t     Press any key to go back!  ");
        getch();
        homepage();
    }
    else if(c==66||c==98){ homepage();} //ASCII FOR B
    else{
        gotoxy(53,19);puts("You entered an invalid choice, ress any key to input again!");
        getch(); journal();
    }
}
int moodsearch(int d, int m,int y, int w){
    FILE *fdmood;
    char userdmood[20];
    int flag=0;
    struct dmood tmood1;
    strcpy(userdmood,username);
    strcat(userdmood,"_dmood.dat");
    fdmood=fopen(userdmood,"rb+"); 
    while(fread(&tmood1, sizeof(tmood1), 1, fdmood)>0 && flag==0){
        if(d==tmood1.day && m==tmood1.mon && y==tmood1.yr && w==tmood1.wday){
            flag++;
            printf("|%s ",tmood1.mood);
            fclose(fdmood);
            return 0;
        }
    } 
    if (flag==0){
    puts("|--");
    fclose(fdmood);
    return 0;
    }
}
int dailymoodtracker(){
    system("cls"); system("color 10");
    gotoxy(150,1); puts("Exit[E]");
    headerdesign();
    gotoxy(70,7);puts(":::Daily Mood Tracker:::");
    gotoxy(35,10);puts("Love [L]");
    gotoxy(60,10);puts("Happy [H]");
    gotoxy(85,10);puts("Sad [S]");
    gotoxy(110,10);puts("Angry [A]");
    gotoxy(135,10);puts("Worried [W]");
    gotoxy(35,11);puts("(UwU)");
    gotoxy(60,11);puts("(*^_^*)");
    gotoxy(85,11);puts("(T_T)");
    gotoxy(110,11);puts("(-_-+)");
    gotoxy(135,11);puts("(^~^;)");
    gotoxy(68,16);puts("How do you feel today?");
    gotoxy(95,16); c=getch();
    c=tolower(c);
    //if(isalpha(c)==0){gotoxy(54,18);printf("Invalid input! "); printf("Enter any key to input again!");getch(); dailymoodtracker();}
    if(c!='l'&& c!='h'&&c!='s'&&c!='a'&&c!='w'){ gotoxy(54,18);printf("Invalid input! "); printf("Enter any key to input again!");getch(); dailymoodtracker();}
    else if(c==69||c==101) exitpage();  //ASCII FOR e
    else dmood_check(c);
    return 0;
}
int dmood_check(char ch){
    time_t secs= time(NULL);
    struct tm t = *localtime(&secs);
    FILE *fdmood;
    char userdmood[20];
    int flag=0;
    struct dmood tmood1;
    strcpy(userdmood,username);
    strcat(userdmood,"_dmood.dat");
    fdmood=fopen(userdmood,"ab+"); 
    while(fread(&tmood1, sizeof(tmood1), 1, fdmood)>0 && flag==0){
        if(t.tm_mday==tmood1.day && t.tm_mon+1==tmood1.mon && t.tm_year+1900==tmood1.yr){
            flag++;
            fclose(fdmood);
            return 0;
        }
    }
    if(flag==0) {
        switch(ch){
            case 76:
            case 108:{
            struct dmood tmood={t.tm_mday,t.tm_mon +1,t.tm_year +1900,t.tm_wday,"Love"};
            fwrite(&tmood,sizeof(tmood),1,fdmood); fclose(fdmood); homepage();}   //ASCII FOR L
            break;
            case 72:
            case 104:{
            struct dmood tmood={t.tm_mday,t.tm_mon +1,t.tm_year +1900,t.tm_wday,"Happy"};
            fwrite(&tmood,sizeof(tmood),1,fdmood); fclose(fdmood); homepage();}   //ASCII FOR H
            break;
            case 83:
            case 115:{
            struct dmood tmood={t.tm_mday,t.tm_mon +1,t.tm_year +1900,t.tm_wday,"Sad"};
            fwrite(&tmood,sizeof(tmood),1,fdmood); fclose(fdmood); homepage();}   //ASCII FOR S
            break;
            case 65:
            case 97:{
            struct dmood tmood={t.tm_mday,t.tm_mon +1,t.tm_year +1900,t.tm_wday,"Angry"};
            fwrite(&tmood,sizeof(tmood),1,fdmood);  fclose(fdmood); homepage();}    //ASCII FOR A
            break;
            case 87:
            case 119:{
            struct dmood tmood={t.tm_mday,t.tm_mon +1,t.tm_year +1900,t.tm_wday,"Worried"};
            fwrite(&tmood,sizeof(tmood),1,fdmood); fclose(fdmood); homepage();}    //ASCII FOR W
            break;
        }
    }
    return 1;    
}
void monthmood(){
        int j=2,k=5,l=6;
        time_t secs= time(NULL);
        system("cls");
        headerdesign();
        gotoxy(70,3); puts("::: Mood Insights :::");
        for(int i=29;i>=0;i--){
            secs=secs-(86400*i);
            struct tm t = *localtime(&secs); // to find out dates of previous 30 days 
            if(j==162){j=2,k+=3,l+=3;}
            gotoxy(j,k); printf("%s, %.3s %d ",days[t.tm_wday].day, month[t.tm_mon].mname,t.tm_mday);
            gotoxy(j,l);moodsearch(t.tm_mday,t.tm_mon+1,t.tm_year+1900,t.tm_wday);
            j+=20;
            secs= time(NULL);
        }
        gotoxy(60,18);puts("Enter any key to go back to the previous page");
        gotoxy(108,18);getch();
        homepage();
}
void signup(){
    struct user U,u;
    FILE *fuser;
    system("cls"); system("color 85");
    fuser = fopen ("username.dat", "ab+");
    if (fuser == NULL){
        printf("\nError opening the file\n");
        exit (1);
    }
    gotoxy(150,1); puts("Exit[E]");
    headerdesign();
    gotoxy(70,4);puts("----REGISTER----");
    gotoxy(70,6);puts("Create Your Account");
    gotoxy(55,10);puts("Enter your First Name: ");
    gotoxy(55,11);puts("Enter your Last Name: ");
    gotoxy(55,12);puts("Enter an Username: ");
    gotoxy(55,13);puts("Enter a Password: ");
    fflush(stdin);
    gotoxy(85,10);gets(U.fname); 
    for(int i=0; i<strlen(U.fname);i++){
     if(isalpha(U.fname[i])==0) {gotoxy(48,16);printf("Name can only be in alphabets!  "); printf("Enter any key to input again!");getch(); signup();}}
    gotoxy(85,11);gets(U.lname); fflush(stdin);
    for(int i=0; i<strlen(U.fname);i++){
    if(isalpha(U.lname[i])==0) {gotoxy(48,16);printf("Name can only be in alphabets!  "); printf("Enter any key to input again!");getch(); signup();}}
    gotoxy(85,12);scanf("%s",U.username); 
    while(fread(&u, sizeof(u), 1, fuser)){
        if(strcmp(u.username,U.username) == 0){
            gotoxy(48,14);puts("**Username already taken, please enter a new username**");
            gotoxy(60,16);puts(" Press any key to continue...");
            gotoxy(95,16); c=getch();
            exitif(c);
            signup();
        }
    }
    gotoxy(85,13);scanf("%s",U.pass);
    fwrite(&U, sizeof(U), 1, fuser);
    userinfo=U;
    strcpy(username,userinfo.username);
    fclose (fuser);
    gotoxy(60,17);puts("***Account Created Successfully***");
    gotoxy(63,19);puts("Press any key to GET STARTED!!");
    gotoxy(95,19);c=getch();
    exitif(c);
    frontpage();
}
void login(){
    char uname[20],pss[20];
    int flag=0;
    FILE *fuser;
    struct user u;
    system("cls"); system("color 85");
    gotoxy(150,1); puts("Exit[E]");
    headerdesign();
    gotoxy(74,5); puts("Hello Again!");
    gotoxy(65,6); puts("Welcome Back you've been missed!");
    gotoxy(58,12); puts("Enter your Username: ");
    gotoxy(58,13); puts("Enter your Password: ");
    gotoxy(80,12); scanf("%s",uname); 
    gotoxy(80,13); scanf("%s",pss);

    fuser=fopen("username.dat","rb+");
    if(fuser==NULL){
        printf("File not found!");
        menu();
    }
    while(fread(&u, sizeof(u), 1, fuser)>0 && flag==0){
        if(strcmp(uname,u.username) == 0 && strcmp(pss,u.pass)==0){
            gotoxy(66,17); puts("**Successfully logged in!**");
            gotoxy(64,19); puts("Press any key to GET STARTED!!");
            gotoxy(100,19); c=getch();
            exitif(c);
            userinfo=u;
            strcpy(username,userinfo.username);
            flag++;
        }
    }
    if(flag==0){
            gotoxy(66,17); puts("Username or Password is Incorrect!");
            gotoxy(66,19); puts("  Press any key to continue...");
            gotoxy(100,19); c=getch();
            exitif(c);
            login();
        }
    fclose(fuser);
    frontpage();
}
int menu(){
    system("cls"); system("color 57");
    char choice;
    int ch;
    headerdesign();
    gotoxy(53,4); puts("There is hope, even when your brain tells you there isn\'t.");
    gotoxy(75,14); puts("SIGNUP [S]");
    gotoxy(75,15); puts("LOGIN [L]");
    gotoxy(75,16); puts("EXIT [E]");
    gotoxy(61,18); puts(" Enter your choice to proceed: ");
    gotoxy(95,18); choice=getchar();
    ch=tolower(choice);
    return ch; 
}
void headerdesign(){
    gotoxy(70,1); puts("<--<< MIND PILL >>-->");
    gotoxy(45,2); for(int i=1;i<75;i++) {printf("~");}
}
void darktheme(){
    system("cls"); system("color 02"); headerdesign();
}
void timer(int x, int y,int h, int m, int s){
    while(1){ 
        gotoxy(x,y); printf("%d:%d:%d",h,m,s);
		Sleep(1000); //it is 1 second
		if(s!=0) { s--; }
		if(s==0 && m!=0) { s=59; m--; }
		if(s==0 && m==0 && h!=0) { h--; m=59; s=59;}
		if(h==0 && m==0 && s==0) { gotoxy(x,y); printf("0:0:0"); break; }
	}
}
void exitif(char n){
    if(n==69||n==101){exitpage();}
}
void exitpage(){
    system("cls"); system("color 07");
        gotoxy(70,5); puts("You've exited the program!");
        exit(0);
        }
void gotoxy(int x,int y){
        COORD c;
        c.X=x;
        c.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void quote(){
    time_t secs= time(NULL);
    srand((unsigned) secs);
    struct quotes q[]={
"You are not your thoughts."
,"One step at a time."
,"It's okay to not be okay."
,"Your mental health is just as important as your physical health."
,"You are stronger than your struggles."
,"Take care of yourself, you deserve it."
,"Mental health is a journey, not a destination."
,"You are not alone in this."
,"Progress, not perfection."
,"Small steps lead to big changes."
,"Breathe, it's just a bad day, not a bad life."
,"Your struggles are valid."
,"You are worthy of love and belonging."
,"Every day is a new beginning."
,"Hope is a powerful thing."
,"It's okay to ask for help."
,"You are capable of great things."
,"Choose kindness, always."
,"Believe in yourself."
,"Your mental health matters."
,"Be kind to yourself, you are doing the best you can."
,"Life is tough, but so are you."
,"It's okay to take a break."
,"Take care of yourself first, everything else can wait."
,"It's okay to not have it all together."
,"You are not defined by your past."
,"Self-care is not selfish."
,"Find joy in the little things."
,"You are stronger than you know."
,"You are not alone, even when it feels like you are."
,"You have the power to change your life."
,"It's okay to be vulnerable."
,"You are worthy of respect and dignity."
,"Take things one day at a time."
,"You are enough, just as you are."
,"You are not your mistakes."
,"You are worthy of happiness."
,"It's okay to say no."
,"You are not a burden."
,"Keep moving forward, even if it's just one step at a time."
,"It's okay to have bad days."
,"You are capable of healing."
,"Your feelings are valid."
,"It's okay to take care of yourself before others."
,"You are not alone in your struggles."
,"You are not your anxiety."
,"Find comfort in the present moment."
,"Your story matters."
,"Be kind to yourself, you are doing the best you can."
,"You are not your depression."
,"You are worthy of love and respect."
,"It's okay to ask for support."
,"You are not weak for struggling."
,"Your feelings are important."
,"It's okay to take a break from everything."
,"You are capable of overcoming obstacles."
,"It\'s okay to not be perfect."
,"You are not alone in your pain."
,"You are capable of change."
,"Your worth is not determined by your productivity."
,"It\'s okay to seek help."
,"You are not your thoughts, you are the observer of them."
,"You are not your illness."
,"Your mental health is worth prioritizing."
,"You are worthy of self-love."
,"It's okay to take time for yourself."
,"You are not your fears."
,"You are capable of resilience."
,"Your mental health is important, no matter what anyone else says"
,"One day at a time."
,"You are not alone."
,"It's okay to not be okay."
,"You are worthy of love and respect."
,"Take care of yourself, you deserve it."
,"You are stronger than your struggles."
,"Believe in yourself."
,"Your mental health is just as important as your physical health."
,"Small steps lead to big changes."
,"It's okay to ask for help."
,"Your feelings are valid."
,"You are not defined by your past."
,"Self-care is not selfish."
,"You are not your thoughts."
,"You are capable of healing."
,"Be kind to yourself, you are doing the best you can."
,"You are not a burden."
,"Your struggles are valid."
,"You are enough, just as you are."
,"Find joy in the little things."
,"You are not your anxiety."
,"Progress, not perfection."
,"It's okay to take a break."
,"You are not weak for struggling."
,"Your story matters."
,"You have the power to change your life."
,"Take things one day at a time."
,"Hope is a powerful thing."
,"It's okay to say no."
,"Your mental health matters."
,"You are not your depression."
,"You are capable of great things."
,"You are not alone in your pain."
,"Your feelings are important."
,"It's okay to have bad days."
,"You are not your illness."
,"You are worthy of happiness."
,"Choose kindness, always."
,"You are not your fears."
,"Find comfort in the present moment."
,"It's okay to not have it all together."
,"Take care of yourself first, everything else can wait."
,"You are capable of resilience."
,"It's okay to seek help."
,"Your worth is not determined by your productivity."
,"You are not your mistakes."
,"You are not alone in your struggles."
,"Your mental health is worth prioritizing."
,"Be gentle with yourself, you're doing the best you can."
,"You are capable of change."
,"You are worthy of self-love."
,"You are not your failures."
,"It's okay to take time for yourself."
,"Your mental health is important, no matter what anyone else says."
,"Breathe, it's just a bad day, not a bad life."
,"You are not your labels."
,"You are not your trauma."
,"You are not your weaknesses."
,"You are not your insecurities."
,"You are not alone in your journey."
,"You are worthy of forgiveness."
,"It's okay to set boundaries."
,"You are capable of self-improvement."
,"You are not your addiction."
,"You are not your limitations."
,"You are not your past mistakes."
,"You are not your job title."
,"You are not your relationship status."
,"You are not your social media presence."
,"You are not your weight or appearance."
,"You are not your financial situation."
,"You are not your academic or professional achievements."};
puts(q[rand()%140].line);
}