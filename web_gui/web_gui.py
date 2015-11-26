#!/usr/bin/python
from http.server import BaseHTTPRequestHandler,HTTPServer
from os import curdir, sep
import serial

PORT_NUMBER = 9000
COM_PORT = 'COM12'
BAUD_RATE = 9600


#This class will handles any incoming request from
#the browser 
class myHandler(BaseHTTPRequestHandler):
	
	#Handler for the GET requests
	def do_GET(self):
		if self.path=="/":
			self.path="/index.html"

		try:

			print("Get request. path %s"%self.path)
			
			# robot control
			if self.path.endswith(".move"):
				if self.path.endswith("forward.move"):
					ser.write('8\n'.encode())
				elif self.path.endswith("stop.move"):
					ser.write('5\n'.encode())
				elif self.path.endswith("reverse.move"):
					ser.write('2\n'.encode())
				elif self.path.endswith("left.move"):
					ser.write('q\n'.encode())
				elif self.path.endswith("right.move"):
					ser.write('e\n'.encode())

				self.send_response(204)  # 204 No content, stay on the same page
				self.end_headers()
				return
			
			if self.path.endswith(".cal"):
				val = int(self.path.rstrip('.cal').lstrip('/'))
				speed1 = 255
				speed2 = 255
				if val >0:
					speed2 -= val
				else:
					speed1 -= val
				s = "S %d %d\n"%(speed1, speed2)
				print(s)
				ser.write(s.encode())
				self.send_response(204)  # 204 No content, stay on the same page
				self.end_headers()
				return				
				
			#Check the file extension required and
			#set the right mime type
			sendReply = False
			if self.path.endswith(".html"):
				mimetype='text/html'
				sendReply = True
			if self.path.endswith(".jpg"):
				mimetype='image/jpg'
				sendReply = True
			if self.path.endswith(".gif"):
				mimetype='image/gif'
				sendReply = True
			if self.path.endswith(".js"):
				mimetype='application/javascript'
				sendReply = True
			if self.path.endswith(".css"):
				mimetype='text/css'
				sendReply = True

			if sendReply == True:
				#Open the static file requested and send it
				isText = True
				if mimetype == 'text/html' or mimetype == 'application/javascript' or mimetype == 'text/css' or mimetype == 'application/javascript':
					f = open(curdir + sep + self.path, 'r')
				else:
					f = open(curdir + sep + self.path, 'rb')  # binary mode for images
					isText = False
				self.send_response(200)
				self.send_header('Content-type',mimetype)
				self.end_headers()
				#print(mimetype)
				if isText:
					#print("%s in text/html"%(curdir + sep + self.path) )
					self.wfile.write(bytes(f.read(), 'utf-8'))
				else:
					#print("%s in else"%(curdir + sep + self.path) )
					self.wfile.write(f.read())
				f.close()
			return


		except IOError:
			self.send_error(404,'File Not Found: %s' % self.path)

try:
	#Create a web server and define the handler to manage the
	#incoming request
	print("Connecting to robot...")
	with serial.Serial(COM_PORT, BAUD_RATE) as ser:
		print("Opened serial port %s at %d"%(COM_PORT, BAUD_RATE))
		server = HTTPServer(('', PORT_NUMBER), myHandler)
		print('Started httpserver on port %d'% PORT_NUMBER)
		
		#Wait forever for incoming htto requests
		server.serve_forever()

except KeyboardInterrupt:
	print('^C received, shutting down the web server')
	server.socket.close()
	ser.close()
