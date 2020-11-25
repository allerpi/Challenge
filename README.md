# Challenge
TC1031 Programación de estructuras de datos y algoritmos fundamentales

Martha Del Río and Valeria Pineda

Program works with C++11 standard onward.

## To run in Terminal (bash or zsh)
1. Open terminal in Challenge directory
2. Run ```/bin/sh runny.sh``` command

## To run in VS Code
1. Ruin Build Task (Command/Ctrl + Shift + B)
2. Change directory to src/
3. Run ```./main.out``` command in Integrated Terminal

## To run in Xcode
1. Add Challenge folder to project
2. Make sure scheme is Challenge/src (Go to Product->Scheme->Edit Scheme->In Run Options use custom working directory and add path to Challenge/src)
3. Add the following Compile Sources: 
   - Entry.cpp
   - Register.cpp
   - ComputerConnections.cpp
   - SiteAccesses.cpp
   - main.cpp
4. Run :)

<details><summary> Questions </summary>

## Part 1
1. How many registers are there in the document?
2. How many records were registered on day 2? What day is this?
3. Do any of the computers belong to Jeffrey, Betty, Katherine, Scott, Benjamin, Samuel or Raymond?
4. What is the internal IP address of the company?
5. Is any computer named "server.reto.com"?
6. What email services are used?

Answers: [here](https://github.com/vpinedagon2000/Challenge/blob/master/1_answers.txt)

## Part 2
1. What IP address are you using?
2. What was the last incoming IP? Is it internal or external?
3. How many incoming connections does this computer have?
4. How many outgoing connections does this computer have?
5. Extra: Does this computer have 3 consecutive connections to the same site?

Answers: [here](https://github.com/vpinedagon2000/Challenge/blob/master/2_answers.txt)

## Part 3
1. Is there  a domain name that is anomalous?
2. From the names found in question 1, what is their IP? How would you determinethis information in the most time-efficient way?
3. From the computers that are part of the domain reto.com, determine the amount of IPs that have at least one incoming connection. Print the amount of computers.
4. Select some computers that aren't server.reto.com or connect to the DHCP server. Find the unique IPs of incoming connections.
5. Taking into account the answers of questions 3 and 4, what do you think is happening within the network?
6. With the IPs found in question 4, determine if these have communicated with the sites from question 1.
7. Extra: If any connections were found in question 6, determine the date and protocol used in the first connection.

Answers: [here](https://github.com/vpinedagon2000/Challenge/blob/master/3_answers.txt)

## Part 4
1. Is there any site that stays in the top 5 every day?
2. Is there any site that enters the top 5 one day and stays there all of the following days?
3. Is there any site that appears in the top 5 with an amount of traffic above the norm?

Answers: [here](https://github.com/vpinedagon2000/Challenge/blob/master/4_answers.txt) 

## Part 5
1. Using the graph with the connections between the IPs and the internal network, determine the amount of computers that A has connected with per day. Is A the vertex that has the most outgoing connections to the internal network?
2. Using the same graph from the first question, locate the amount of computers that have connected with A per day. Are there connections from the other computers to A?
3. Using a graph of connections to websites, determine which computers have connected with B per day.
4. Using the same graph from question 3, poin out how many computers have connected with C per day.
5. Question without code: Search what a ping sweep, a DDoS, a command and control server, and a botmaster are. Do you see these elements in your data?

Answers: [here](https://github.com/vpinedagon2000/Challenge/blob/master/5_answers.txt) 

</details>
