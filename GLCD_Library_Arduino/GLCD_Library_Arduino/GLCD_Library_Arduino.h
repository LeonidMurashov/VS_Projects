
/*
* GLCD_Library_Arduino
*
* Created: 21.03.2016 17:44:45
*  Author: ������
*  GLCD library for Arduino.
*  Only for Arduino Uno
*/

#define TIME_TO_WAIT_BEFORE 0 // 310 //T_WH-T_ASU
#define TIME_TO_WRITE 0 //140 //T_ASU
#define TIME_TO_WAIT_AFTER 0 //450 //T_WH
#define TIME_TO_WAIT_AFTER_WAITING 0 //10 //T_DHW

#define WAITING_TIME_FOR_E 0//3
#define NULL_PIN 255

unsigned char lcd[8][64][2]; //��������>������>CS>data(unsigned char - 8 ���)
unsigned char updateStage = 0;
void E_PULL(); void Lcd_Clear();

class PORT
{
	byte buffer;
	byte pinAdress[8];

	void Reset()
	{
		for (int i = 0; i < 8; i++)
			if (pinAdress[i] != NULL_PIN)
				digitalWrite(pinAdress[i], buffer & (1 << i));
	}

public:
	PORT(byte _pinAdress[])
	{
		memcpy(pinAdress, _pinAdress, sizeof(byte) * 8);
		for (byte adress : pinAdress)
			pinMode(adress, OUTPUT);
	}

	void operator^=(byte _buffer)
	{
		buffer ^= _buffer;
		Reset();
	}

	void operator|=(byte _buffer)
	{
		buffer |= _buffer;
		Reset();
	}

	void operator&=(byte _buffer)
	{
		buffer &= _buffer;
		Reset();
	}

	void operator=(byte _buffer)
	{
		buffer = _buffer;
		Reset();
	}
};

byte portd[8] = { NULL_PIN, NULL_PIN, A1, A0, A3, A2, A4, NULL_PIN };
PORT PORTD_(portd);
byte portc[8] = { 8, 9, 10, 11, 4, 5, 6, 7 };
PORT PORTC_(portc);

void Lcd_Init()
{
	PORTD_ = 0;
	E_PULL();
	PORTD_ = 0b10000000;   //������� � �������������
	PORTC_ = 0b00111111;
	E_PULL();

	Lcd_Clear();
}

void E_PULL() //��� glcd ������ � ������ ����������
{
	PORTD_ |= (1 << 6);   delayMicroseconds(WAITING_TIME_FOR_E); //���� ������
	PORTD_ ^= (1 << 6);   delayMicroseconds(WAITING_TIME_FOR_E); //���� �����
}


void WRITE(unsigned char data)
{
	PORTD_ = 0b10000000; delayMicroseconds(TIME_TO_WAIT_BEFORE);
	PORTC_ = data;      delayMicroseconds(TIME_TO_WRITE);
	E_PULL();
}
void WRITE_D(unsigned char data, int CS)//CS1 or CS2
{
	if (CS == 1)
	{
		PORTD_ = 0b10011000; delayMicroseconds(TIME_TO_WAIT_BEFORE);
		//PORTD_ = 0b10011000; delayMicroseconds(TIME_TO_WAIT_BEFORE);
		PORTC_ = data;       delayMicroseconds(TIME_TO_WRITE);
		E_PULL();
	}
	else if (CS == 2)
	{
		PORTD_ = 0b10010100; delayMicroseconds(TIME_TO_WAIT_BEFORE);
		PORTC_ = data;       delayMicroseconds(TIME_TO_WRITE);
		E_PULL();
	}
}
void Lcd_Clear()
{
	for (int i = 0; i<8; i++)
	{
		PORTD_ = 0b10000000; delayMicroseconds(TIME_TO_WAIT_BEFORE);
		PORTC_ = 0b10111000 + i; delayMicroseconds(TIME_TO_WRITE);
		E_PULL();
		for (int j = 0; j<64; j++)
		{
			PORTD_ = 0b10000000; delayMicroseconds(TIME_TO_WAIT_BEFORE);
			PORTC_ = 0b01000000 + j; delayMicroseconds(TIME_TO_WRITE); //����� ������ �� X
			E_PULL();

			PORTD_ = 0b10010100; delayMicroseconds(TIME_TO_WAIT_BEFORE);
			PORTC_ = 0b00000000; delayMicroseconds(TIME_TO_WRITE);  //�������� � CS1
			E_PULL();

			PORTD_ = 0b10011000; delayMicroseconds(TIME_TO_WAIT_BEFORE);
			PORTC_ = 0b00000000; delayMicroseconds(TIME_TO_WRITE);  //�������� � CS2
			E_PULL();
		}
	}

	for (int i = 0; i<8; i++)
		for (int j = 0; j<64; j++)
		{
			lcd[i][j][0] = 0b00000000;
			lcd[i][j][1] = 0b00000000;
		}
}

void setPixel(unsigned char x, unsigned char y, bool state = true)// 0 - off // 1 - on
{
	if (x<128 && x >= 0 && y >= 0 && y<64 && (state == false || state == true))
	{
		unsigned char page = y / 8, adress, databit = y % 8, CS, data;
		if (x<64) { CS = 0; adress = x; }
		else { CS = 1; adress = x - 64; }

		WRITE(0b01000000 + adress);
		WRITE(0b10111000 + page);
		/*
		if(state)
		for(int i = 0; i<8; i++) if(lcd[page][adress][CS][i] || i == databit) data |= (1<<i);
		else
		for(int i = 0; i<8; i++) if(lcd[page][adress][CS][i] && i!=databit) data |= (1<<i);
		*/
		if (state) data = lcd[page][adress][CS] | (1 << databit);
		else
		{
			data = lcd[page][adress][CS];
			if ((lcd[page][adress][CS]) & (1 << databit)) data -= (1 << databit);
		}

		WRITE_D(data, CS ? 2 : 1); //����� ��������

		if (state)lcd[page][adress][CS] |= (1 << databit);
		else
		{
			if (lcd[page][adress][CS] & (1 << databit)) lcd[page][adress][CS] -= (1 << databit);
		}
	}
}

void Lcd_Fill()
{
	for (int i = 0; i<8; i++)
	{
		PORTD_ = 0b10000000; delayMicroseconds(TIME_TO_WAIT_BEFORE);
		PORTC_ = 0b10111000 + i; delayMicroseconds(TIME_TO_WRITE);
		E_PULL();
		for (int j = 0; j<64; j++)
		{
			PORTD_ = 0b10000000; delayMicroseconds(TIME_TO_WAIT_BEFORE);
			PORTC_ = 0b01000000 + j; delayMicroseconds(TIME_TO_WRITE); //����� ������ �� X
			E_PULL();

			PORTD_ = 0b10010100; delayMicroseconds(TIME_TO_WAIT_BEFORE);
			PORTC_ = 0b11111111; delayMicroseconds(TIME_TO_WRITE);  //�������� � CS1
			E_PULL();

			PORTD_ = 0b10011000; delayMicroseconds(TIME_TO_WAIT_BEFORE);
			PORTC_ = 0b11111111; delayMicroseconds(TIME_TO_WRITE);  //�������� � CS2
			E_PULL();
		}
	}
	for (int i = 0; i<8; i++)
		for (int j = 0; j<64; j++)
			for (int o = 0; o<8; o++)
			{
				lcd[i][j][0] = 0b11111111;
				lcd[i][j][1] = 0b11111111;
			}
}

void swap(int &a, int &b)
{
	int c = a - b;
	b = a;
	a = b + c;
}

void line(int x1, int y1, int x2, int y2, bool state = true)
{
	int dx = (x2 - x1 >= 0 ? 1 : -1);
	int dy = (y2 - y1 >= 0 ? 1 : -1);

	int lengthX = abs(x2 - x1);
	int lengthY = abs(y2 - y1);

	int length = max(lengthX, lengthY);

	if (length == 0)
	{
		setPixel(x1, y1, state);
	}

	if (lengthY <= lengthX)
	{
		// ��������� ��������
		int x = x1;
		int y = y1;
		int d = -lengthX;

		// �������� ����
		length++;
		while (length--)
		{
			setPixel(x, y, state);
			x += dx;
			d += 2 * lengthY;
			if (d > 0) {
				d -= 2 * lengthX;
				y += dy;
			}
		}
	}
	else
	{
		// ��������� ��������
		int x = x1;
		int y = y1;
		int d = -lengthY;

		// �������� ����
		length++;
		while (length--)
		{
			setPixel(x, y, state);
			y += dy;
			d += 2 * lengthX;
			if (d > 0) {
				d -= 2 * lengthY;
				x += dx;
			}
		}
	}
}

void circle(int x0, int y0, int radius, bool state = trueint
{
	) x = radius;
	int y = 0;
	int radiusError = 1 - x;
	while (x >= y)
	{
		setPixel(x + x0, y + y0, state);
		setPixel(y + x0, x + y0, state);
		setPixel(-x + x0, y + y0, state);
		setPixel(-y + x0, x + y0, state);
		setPixel(-x + x0, -y + y0, state);
		setPixel(-y + x0, -x + y0, state);
		setPixel(x + x0, -y + y0, state);
		setPixel(y + x0, -x + y0, state);
		y++;
		if (radiusError < 0)
		{
			radiusError += 2 * y + 1;
		}
		else
		{
			x--;
			radiusError += 2 * (y - x + 1);
		}
	}
}