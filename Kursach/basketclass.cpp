#include "basketclass.h"
#include "qvariant.h"

QList<Basket::CartItem> Basket::cart = QList<Basket::CartItem>();

Basket::Basket()
{

}

//bool Basket::addToCart(int productId, const QString& name, const QString& description , int quantity, int price, int discount)
bool Basket::addToCart(QSqlRecord sql)
{
    int productId = sql.value(0).toInt();
    QString name = sql.value(1).toString();
    QString description = sql.value(2).toString();
    int price = sql.value(3).toInt();
    int quantity = sql.value(4).toInt();
    int discount = sql.value(5).toInt();

    bool found = false;
    if(quantity == 0) return false;

    for (int i = 0; i < cart.size(); ++i) {
        if (cart[i].productId == productId) {
            if(cart[i].quantity < quantity)
            {
                cart[i].quantity += 1;
                cart[i].price += price;
                found = true;
                break;
                //return true;
            }
            else return false;
        }
    }

    // Если товар не найден, добавляем его как новую запись
    if (!found) {
        CartItem newItem = {productId, name, description, price, 1,  discount};
        cart.append(newItem);
        return true;
    }
    return true;
}

void Basket::removeFromCart(int productId, int mode) {
    for (int i = 0; i < cart.size(); ++i) {
        if (cart[i].productId == productId) {
            cart[i].price = cart[i].price / cart[i].quantity;
            cart[i].quantity -= 1;
            if (cart[i].quantity == 0 || mode == 2) {
                cart.removeAt(i);
                return;
            }
            cart[i].price = cart[i].price * cart[i].quantity;

            return;
        }
    }
}
void Basket::clearCart()
{
    cart.clear();
}

QList<Basket::CartItem> Basket::getCartItems() {
    return cart;
}

