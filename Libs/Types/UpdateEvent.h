#ifndef UPDATEEVENT_H
#define UPDATEEVENT_H

#include <QRect>
#include <QVector>
#include <QByteArray>
#include <QDataStream>
#include "Bit.h"
#include "Event.h"

class UpdateEvent:public Event
{
private:
	QRect rect;
	QVector<BitType> bitmap;

public:
	UpdateEvent(const QByteArray &data=QByteArray())
	{
		if(!data.isEmpty()){
			QDataStream stream(data);
			EventType type;
			stream>>type;
			if(type==Update){
				stream>>rect>>bitmap;
			}
		}
	}

	QByteArray toByteArray() const
	{
		QByteArray data;
		QDataStream stream(&data,QIODevice::WriteOnly);
		EventType type=Update;
		stream<<type<<rect<<bitmap;
		return data;
	}

	inline const QRect &getRect() const {return rect;}
	inline void setRect(const QRect &rect){this->rect=rect;}

	inline const QVector<BitType> &getBitmap() const {return bitmap;}
	inline void setBitmap(const QVector<BitType> &bitmap){this->bitmap=bitmap;}

	inline bool isEmpty() const {return bitmap.isEmpty();}
	inline bool isValid() const {return bitmap.size()==rect.width()*rect.height();}
};

#endif // UPDATEEVENT_H
