p =  7927;
a = 500;
b = 0;
E = EllipticCurve(GF(p), [a, b]);

print(E.points()[:10])  

P = E(188, 93);
print 'P=', P;
print 'P+P=', P+P;

P = E(692, 150);
print 'P=', P;
print 'P+P=', P+P;

P = E(6026, 210);
print 'P=', P;
print 'P+P=', P+P;

P = E(6026, 210);
Q = E(2, 2903);
print 'P=', P;
print 'Q=', Q;
print 'P+Q=', P+Q;

P = E(4, 5017);
Q = E(475, 2499);
print 'P=', P;
print 'Q=', Q;
print 'P+Q=', P+Q;

p = 6277101735386680763835789423207666416102355444459739541047;
a = 0;
b = 3;
E = EllipticCurve(GF(p), [a, b]);
P = E(5377521262291226325198505011805525673063229037935769709693, 3805108391982600717572440947423858335415441070543209377693);
Q = P + P;
print 'P=', P;
print 'P+P=', P+P;
print 'Q=', Q;
print 'P + Q=', P+Q;
