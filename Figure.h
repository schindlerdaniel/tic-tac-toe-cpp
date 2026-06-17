#ifndef FIGURE_H
#define FIGURE_H



class Figure {
public:
    virtual char getSymbol() const = 0;
    virtual ~Figure() {}
};


class XFigure : public Figure {
public:
    virtual char getSymbol() const;
};



class OFigure : public Figure {
public:
    virtual char getSymbol() const;

};



#endif // FIGURE_H









