int trig = 13;
int echo = 12;

float distancia;

int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;

int irSensorEsquerda = 8;
int irSensorDireita = 9;

void setup()
{
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);

    pinMode(irSensorEsquerda, INPUT);
    pinMode(irSensorDireita, INPUT);

    Serial.begin(9600);
}

void loop()
{
    int leituraIrEsquerda = digitalRead(irSensorEsquerda);
    int leituraIrDireita = digitalRead(irSensorDireita);

    // Verifica se os sensores detectam branco
    if (leituraIrEsquerda == HIGH || leituraIrDireita == HIGH)
    {
        // Entrar em modo de busca: girar para a direita
        girarMotorAHorario();
        girarMotorBAntiHorario();
        Serial.println("PROCURANDO INIMIGO!!! (MODO DE BUSCA)");
        delay(500);
    }
    else
    {
        // Medir a distância com o sensor ultrassônico
        digitalWrite(trig, LOW);
        delay(5);
        digitalWrite(trig, HIGH);
        delay(10);
        digitalWrite(trig, LOW);

        distancia = pulseIn(echo, HIGH);
        distancia = distancia / 58;
        Serial.println(distancia);

        // Verifica se há inimigo próximo
        if (distancia < 10)
        {
            girarMotorAHorario();
            girarMotorBHorario();
            Serial.println("INIMIGO DETECTADO!!!");
            delay(500);
        }
        else
        {
            pararMotorA();
            girarMotorBHorario();
            Serial.println("PROCURANDO INIMIGO!!!");
            delay(500);
        }
    }
}

void girarMotorAHorario()
{
    // Gira o Motor A no sentido horário
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
}

void pararMotorA()
{
    // Para o motor A
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
}

void girarMotorBHorario()
{
    // Gira o Motor B no sentido horário
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void pararMotorB()
{
    // Para o motor B
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
}

void girarMotorAAntiHorario()
{
    // Gira o Motor A no sentido anti-horário
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
}

void girarMotorBAntiHorario()
{
    // Gira o Motor B no sentido anti-horário
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

