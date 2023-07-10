#include <iostream>
#include <vector>
#define random(a,b) a+rand()%(b+1-a)
using namespace std;

class Bullet {
    friend class FlyWeightBullet;
    friend class FlyWeightArrow;
    friend class FlyWeightFireball;
protected:
    string type;
    string sprite;
    string color;
    int power;
    float radius;

};

class Fireball: public Bullet {

public:
    Fireball(string sprite,
            string color,
            int power,
            float radius) {
        this->sprite = sprite;
        this->color = color;
        this->power = power;
        this->radius = radius;
        this->type = "fireball";
    }


};

class  Arrow: public Bullet {

public:
    Arrow(string sprite,
        string color,
        int power,
        float radius) {
        this->sprite = sprite;
        this->color = color;
        this->power = power;
        this->radius = radius;
        this->type = "arrow";
    }

};

class FlyWeightBullet {
protected:
    Bullet* object;
    int X;
    int Y;
public:
    FlyWeightBullet(Bullet* object, int X, int Y) {
        this->object = object;
        this->X = X;
        this->Y = Y;
    }
    virtual void shoot() = 0;

};

class FlyWeightArrow: public FlyWeightBullet {
public:
    FlyWeightArrow(Arrow* object, int X, int Y): FlyWeightBullet(object, X, Y) {}
    void shoot() {
        cout << " летит стрела: ";
        cout << object->color << " : ";
        cout << object->sprite << " : " << object->power << " : " << object->radius << endl;
    }
};

class FlyWeightFireball : public FlyWeightBullet {
public:
    FlyWeightFireball(Fireball* object, int X, int Y) : FlyWeightBullet(object, X, Y) {}
    void shoot() {
        cout << " летит фаерболл: ";
        cout << object->color << " : ";
        cout << object->sprite << " : " << object->power << " : " << object->radius << endl;
    }
};

class FireballFactory {
    Fireball* fBall = nullptr;
public:
    FireballFactory(string sprite, string color, int power, float radius) {
        fBall = new Fireball(sprite, color, power, radius);
    }
    FlyWeightBullet* createBullet(int X, int Y) {
        return new FlyWeightFireball(fBall, X, Y);
    }
};

class ArrowFactory {
    Arrow* fBall = nullptr;
public:
    ArrowFactory(string sprite, string color, int power, float radius) {
        fBall = new Arrow(sprite, color, power, radius);
    }
    FlyWeightBullet* createBullet(int X, int Y) {
        return new FlyWeightArrow(fBall, X, Y);
    }
};

class BulletFactory {
    FireballFactory* fFactory = nullptr;
    ArrowFactory* aFactory = nullptr;
    vector <FlyWeightBullet*> magazine;
public:
    BulletFactory() {
        fFactory = new FireballFactory("fire.jpg", "red", 40, 23);
        aFactory = new ArrowFactory("arrow.jpg", "green", 20, 15);
    }
    void appendBullet(string type) {
        if (type == "arrow") {
            magazine.push_back(aFactory->createBullet(random(0, 100), random(0, 100)));
        }
        else if (type == "fireball") {          
            magazine.push_back(fFactory->createBullet(random(0, 100), random(0, 100)));
        }
    }
    void shootAll() {
        for (auto bul : magazine) {
            bul->shoot();
        }
    }
};


int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "");
    BulletFactory* factory = new BulletFactory();
    for (int i = 0; i < 10; i++) {
        factory->appendBullet("arrow");
    }
    for (int i = 0; i < 20; i++) {
        factory->appendBullet("fireball");
    }

    factory->shootAll();

    
}
