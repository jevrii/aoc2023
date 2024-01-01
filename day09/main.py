from scipy.interpolate import lagrange
ys = [13,33,54,85,159,343,748,1539,2945,5269,8898,14313,22099,32955,47704,67303,92853,125609,166990,218589,282183]
xs = [i for i in range(0, len(ys))]
poly = lagrange(xs, ys)
print(poly(len(xs)))
