# LBB---Arduino

####Serial write command structure: 
######(senzor_id);(senzor_state);(parameter - if needed)

####LBB-ENDPOINT-ID
######1 - SERVO
######2 - TEMPERATURE

####SERVO MOTOR
######WRITE - 1 (Int angle parameter between 0 - 180)
######READ - 2 (Returns current servo angle)

####TEMPERATURE STATE
######READ - 1 (Returns current temperature)

