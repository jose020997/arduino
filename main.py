#Lectura matricula no incluido
#Falta el pago

import mysql.connector
import serial
from datetime import datetime as dt
import time
import lecturamatriculassimple

#Puertos serie cada uno segun el esquema realizado
# PuertoSerie1 = serial.Serial('COM1', 9600)
PuertoSerie2 = serial.Serial('COM6', 9600)
PuertoSerie3 = serial.Serial('COM7', 9600)

#Lectura de matricula en caso de implementarlo
#ruta_imagen = 'auto002.jpg'
#matricula = lecturamatriculassimple.obtener_matricula(ruta_imagen).replace(" ","").replace("\n", "")
#print(matricula)

# Establecer la conexión a la base de datos
conexion = mysql.connector.connect(
    host="localhost",
    user="jose",
    password="jose",
    database="sensores"
)

def insertar_datos(conexion, valor1,valor2,valor3):
    cursor = conexion.cursor()
    consulta = "INSERT INTO matriculas (ID, matricula,entrada,tiempo,pagado) VALUES (NULL, %s, %s,%s,%s);"
    fecha_actual = dt.now().strftime("%d:%m-%H:%M:%S")
    valores = (valor1,valor2, fecha_actual,valor3)

    cursor.execute(consulta, valores)
    conexion.commit()

def consulta_precio(conexion, valor1):
    cursor = conexion.cursor()
    consulta = "SELECT tiempo FROM matriculas WHERE matricula = %s ORDER BY tiempo DESC;"
    
    cursor.execute(consulta, (valor1,))
    resultados = cursor.fetchall()
    
    #print("Consulta SQL:", cursor.statement)
    
    if len(resultados) >= 2:
        primer_valor = resultados[0][0]
        segundo_valor = resultados[1][0]
        #print("Primer valor:", primer_valor)
        #print("Segundo valor:", segundo_valor)

        tiempo_hora1=primer_valor.split("-")[1]
        hora1=int(tiempo_hora1.split(":")[0])*60
        minutos1=int(tiempo_hora1.split(":")[1])
        segundos1=int(tiempo_hora1.split(":")[2])/60

        #print(hora1+minutos1+segundos1)

        tiempo_hora2=segundo_valor.split("-")[1]
        hora2=int(tiempo_hora2.split(":")[0])*60
        minutos2=int(tiempo_hora2.split(":")[1])
        segundos2=int(tiempo_hora2.split(":")[2])/60

        #Precio de la tarifa
        tarifa=0.10

        precio=((hora1+minutos1+segundos1)-(hora2+minutos2+segundos2))*tarifa
        return(precio)

def insertar_maximocoches(conexion, valor1):
    cursor = conexion.cursor()
    consulta = "INSERT INTO totalcoches (ID, matricula) VALUES (NULL, %s);"
    valores = (valor1,)

    cursor.execute(consulta, valores)
    conexion.commit()

def delete_maximocoches(conexion, valor1):
    cursor = conexion.cursor()
    consulta = "DELETE FROM totalcoches WHERE matricula = %s;"
    valores = ((valor1,))

    cursor.execute(consulta, valores)
    conexion.commit()

def calcular_coches_dentro(conexion):
    cursor = conexion.cursor()
    consulta = "SELECT * FROM totalcoches;"
    cursor.execute(consulta)
    resultados = cursor.fetchall()
    return(len(resultados))

def poner_pagado(conexion, valor1):
    cursor = conexion.cursor()
    consulta = "UPDATE matriculas SET pagado='1' where matricula= %s;"
    valores = ((valor1,))

    cursor.execute(consulta, valores)
    conexion.commit()

def sensor_luz1(conexion, valor1):
    cursor = conexion.cursor()
    consulta = "INSERT INTO sensor_luz (ID, Vluz) VALUES (NULL, %s);"
    valores = ((valor1,))

    cursor.execute(consulta, valores)
    conexion.commit()

def sensor_luz2(conexion, valor1):
    cursor = conexion.cursor()
    consulta = "INSERT INTO sensor_luz2 (ID, Vluz) VALUES (NULL, %s);"
    valores = ((valor1,))

    cursor.execute(consulta, valores)
    conexion.commit()

def temperatura(conexion, valor1):
    cursor = conexion.cursor()
    consulta = "INSERT INTO temp (ID, vgrado) VALUES (NULL, %s);"
    valores = ((valor1,))

    cursor.execute(consulta, valores) 
    conexion.commit()

def temperatura2(conexion, valor1):
    cursor = conexion.cursor()
    consulta = "INSERT INTO temp2 (ID, vgrado) VALUES (NULL, %s);"
    valores = ((valor1,))

    cursor.execute(consulta, valores)  
    conexion.commit() 

#Base de datos acceso para el arduino III
def humedad1(conexion, valor1):
    cursor = conexion.cursor()
    consulta = "INSERT INTO humedad1 (ID, vhumedad) VALUES (NULL, %s);"
    valores = ((valor1,))

    cursor.execute(consulta, valores)
    conexion.commit()

def humedad2(conexion, valor1):
    cursor = conexion.cursor()
    consulta = "INSERT INTO humedad2 (ID, vhumedad) VALUES (NULL, %s);"
    valores = ((valor1,))

    cursor.execute(consulta, valores)
    conexion.commit()

def humedad3(conexion, valor1):
    cursor = conexion.cursor()
    consulta = "INSERT INTO humedad3 (ID, vhumedad) VALUES (NULL, %s);"
    valores = ((valor1,))

    cursor.execute(consulta, valores)
    conexion.commit()

def humedad4(conexion, valor1):
    cursor = conexion.cursor()
    consulta = "INSERT INTO humedad4 (ID, vhumedad) VALUES (NULL, %s);"
    valores = ((valor1,))

    cursor.execute(consulta, valores)  
    conexion.commit()  

def cantidad_agua(conexion, valor1):
    cursor = conexion.cursor()
    consulta = "INSERT INTO cantidad_agua (ID, Valor) VALUES (NULL, %s);"
    valores = ((valor1,))

    cursor.execute(consulta, valores)  
    conexion.commit()

def cantidad_agua2(conexion, valor1):
    cursor = conexion.cursor()
    consulta = "INSERT INTO cantidad_agua2 (ID, Valor) VALUES (NULL, %s);"
    valores = ((valor1,))

    cursor.execute(consulta, valores)  
    conexion.commit()

#Arduino II
#Sensor de luz
def luz1(conexion, valor1):
    cursor = conexion.cursor()
    consulta = "INSERT INTO sensor_luz (ID, Vluz) VALUES (NULL, %s);"
    valores = ((valor1,))

    cursor.execute(consulta, valores)  
    conexion.commit()

def luz2(conexion, valor1):
    cursor = conexion.cursor()
    consulta = "INSERT INTO sensor_luz2 (ID, Vluz) VALUES (NULL, %s);"
    valores = ((valor1,))

    cursor.execute(consulta, valores)  
    conexion.commit()

#Sensor Distancia Motores
#Hora en la cual ponemos el motorcito a funcionar I
def es_hora_de_activar():
    now = dt.now()
    return now.hour == 20 and now.minute == 43


#Arduino I
def parkingI(conexion, valor1):
    cursor = conexion.cursor()
    consulta = "INSERT INTO distancia2 (ID, distancia) VALUES (NULL, %s);"
    valores = ((valor1,))

    cursor.execute(consulta, valores)  
    conexion.commit()

def del_parkingI(conexion):
    cursor = conexion.cursor()
    consulta = "DELETE FROM distancia2;"
    cursor.execute(consulta,)  
    conexion.commit()

def check_parkingI(conexion):
    cursor = conexion.cursor()
    consulta = "Select * FROM distancia2;"
    cursor.execute(consulta,)
    resultados = cursor.fetchall()
    return(len(resultados))

def parkingII(conexion, valor1):
    cursor = conexion.cursor()
    consulta = "INSERT INTO distancia3 (ID, distancia) VALUES (NULL, %s);"
    valores = ((valor1,))

    cursor.execute(consulta, valores)  
    conexion.commit()

def del_parkingII(conexion):
    cursor = conexion.cursor()
    consulta = "DELETE FROM distancia3;"
    cursor.execute(consulta,)  
    conexion.commit()

def check_parkingII(conexion):
    cursor = conexion.cursor()
    consulta = "Select * FROM distancia3;"
    cursor.execute(consulta,)
    resultados = cursor.fetchall()
    return(len(resultados))

def parkingIII(conexion, valor1):
    cursor = conexion.cursor()
    consulta = "INSERT INTO distancia4 (ID, distancia) VALUES (NULL, %s);"
    valores = ((valor1,))

    cursor.execute(consulta, valores)  
    conexion.commit()

def del_parkingIII(conexion):
    cursor = conexion.cursor()
    consulta = "DELETE FROM distancia4;"
    cursor.execute(consulta,)  
    conexion.commit()

def check_parkingIII(conexion):
    cursor = conexion.cursor()
    consulta = "Select * FROM distancia4;"
    cursor.execute(consulta,)
    resultados = cursor.fetchall()
    return(len(resultados))   

ruta_imagen = 'auto002.jpg'
matricula = lecturamatriculassimple.obtener_matricula(ruta_imagen).replace(" ","").replace("\n", "")

contador=0;
#Comienzo del programa
while True:


    time.sleep(1)

    # Arduino I
    for _ in range(4):
        # lectura3 = PuertoSerie3.readline().strip().decode('utf-8')
        # #print(lectura3)
        # if lectura3.startswith("Distancia1:"):
        #     dista1 = float(lectura3.split(":")[1])
        #     print("dista1")
        #     print(dista1)
        #     if dista1<=4:
        #         if(check_parkingI(conexion)==0):
        #             parkingI(conexion,1)
        #             print("Insert")
        #     else:
        #         del_parkingI(conexion)
        #         print("del")

        # if lectura3.startswith("Distancia2:"):
        #     dista2 = float(lectura3.split(":")[1])
        #     print("dista2")
        #     print(dista2)
        #     if dista2<=4:
        #         if(check_parkingII(conexion)==0):
        #             parkingII(conexion,1)
        #             print("Insert")
        #     else:
        #         del_parkingII(conexion)
        #         print("del")

        # if lectura3.startswith("Distancia3:"):
        #     dista3 = float(lectura3.split(":")[1])
        #     print("dista3")
        #     print(dista3)
        #     if dista3<=4:
        #         if(check_parkingIII(conexion)==0):
        #             parkingIII(conexion,1)
        #             print("check")
        #     else:
        #         del_parkingIII(conexion)
        #         print("del")

        #     #Luz verde y luz roja
        # if lectura3.startswith("Sobra"):    
        #     total=calcular_coches_dentro(conexion)
        #     print(total)
        #     if(total<=3):
        #         print("Luz verde")
        #         #Enviamos el dato 10 al arduino 3
        #         dato_a_enviar = "10"
        #         PuertoSerie3.write(dato_a_enviar.encode())
        #     else:
        #         print("Luz roja")
        #         #Enviamos el dato 20 al arduino 3
        #         dato_a_enviar = "20"
        #         PuertoSerie3.write(dato_a_enviar.encode())




   #Arduino II

    # #Activamos el motor si tenemos una distancia de menos de 3 metros
    
        lectura2 = PuertoSerie2.readline().strip().decode('utf-8')
        # print(lectura2)
        # if contador==6:
        #     print("Alo moto")
        #     if lectura2.startswith("luz1:"):
        #         luz1 = int(float(lectura2.split(":")[1]))
        #         print(luz1)
        #         sensor_luz1(conexion, luz1)
        #     if lectura2.startswith("luz2:"):
        #         luz2 = int(float(lectura2.split(":")[1]))
        #         print(luz2)
        #         sensor_luz2(conexion, luz2)
        #     contador=-1
        
    #     if lectura2.startswith("Distancia4:"):
    #         Distancia_motor1 = float(lectura2.split(":")[1])
    #         print(Distancia_motor1)
    #         if Distancia_motor1 <= 6:
    #             dato_a_enviar = "80"
    #             PuertoSerie2.write(dato_a_enviar.encode())
    #             insertar_datos(conexion,matricula,"1","0")
    #             insertar_maximocoches(conexion,matricula)


    # # # Falta la camara con el insert de matricula
    # # # Falta el insert y en el total de coches

    #     if lectura2.startswith("Distancia5:"):
    #         Distancia_motor2 = float(lectura2.split(":")[1])
    #         print(Distancia_motor2)
    #         if Distancia_motor2 <= 6:
    #             dato_a_enviar = "90"
    #             PuertoSerie2.write(dato_a_enviar.encode())
    #             # insertar_datos(conexion,matricula,"1","0")
    #             # coste_sinredondeo=consulta_precio(conexion,matricula)
    #             # coste=round(coste_sinredondeo, 2)
    #             # print(coste)
    #             poner_pagado(conexion,matricula)
    #             delete_maximocoches(conexion,matricula)


    





    #Arduino III
    #Activar motores con alguna condicion
    # print(es_hora_de_activar)
    # if es_hora_de_activar():
    #     print("Motor Agua I")
    # #Enviamos el dato 10 al arduino 3 para activar el motor en el arduino2
    #     dato_a_enviar = "10"
    # #PuertoSerie2.write(dato_a_enviar.encode())

    #     print("Motor Agua II")
    # #Enviamos el dato 40 al arduino 3 para activar el motor en el arduino2
    #     dato_a_enviar = "20"
    # #PuertoSerie2.write(dato_a_enviar.encode())
    
    # #Subir nvl agua
    # if contador==6:
    # if lectura3.startswith("n1:"):
    #         nivelagua1 = int(lectura3.split(":")[1])
    #         cantidad_agua(conexion, nivelagua1)
    #         #conexion.commit()

    # if lectura3.startswith("n2:"):
    #         nivelagua2 = int(lectura3.split(":")[1])
    #         cantidad_agua2(conexion, nivelagua2)
    #         #conexion.commit()

    # #Subir sensor humedad
    # if lectura3.startswith("h1:"):
    #         humedad_1 = int(lectura3.split(":")[1])
    #         humedad1(conexion, humedad_1)
    #         #conexion.commit()

    # if lectura3.startswith("h2:"):
    #         humedad_2 = int(lectura3.split(":")[1])
    #         humedad2(conexion, humedad_2)
    #         #conexion.commit()

    # if lectura3.startswith("h3:"):
    #         humedad_3 = int(lectura3.split(":")[1])
    #         humedad3(conexion, humedad_3)
    #         #conexion.commit()

    # if lectura3.startswith("h4:"):
    #         humedad_4 = int(lectura3.split(":")[1])
    #         humedad4(conexion, humedad_4)
    #         #conexion.commit()
        # contador=-1



    #Tiempo de descanso
    print("Vuelta")
    time.sleep(5)
    contador+=1

#Meter el timing en cada archivo de arduino con lo que tarda en accion para sincronizar