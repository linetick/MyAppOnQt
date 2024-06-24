#ifndef BASKETCLASS_H
#define BASKETCLASS_H
#include <QString>
#include <QList>
#include "qsqlrecord.h"

class Basket
{
public:
    struct CartItem{
        int productId;
        QString name;
        QString description;
        int price;
        int quantity;
        int discount;
    };

public:
    Basket();
   static void clearCart();
   static bool addToCart(QSqlRecord);
   static QList<CartItem> getCartItems();
   static void removeFromCart(int productId, int mode);
private:
   static QList<CartItem> cart;
};

#endif // BASKETCLASS_H
