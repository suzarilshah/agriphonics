# agriphonics
A smart Aquaponics solutions implementing Microsoft Azure, Azure IoT Hub, Azure Stream Job Analytics, Power BI and Power Apps

* This project is an update to my last project: https://github.com/suzarilshah/smartaquaponics 
* Added integration to Azure Cloud, Azure IoT Hub, Stream Jobs Analytics and Microsoft PowerPlatform (PowerApps and PowerBI)
* The Problem statements and Objectives are still the same, but this time, we are targetting SME to large scale Aquaponics Farmers, implementing Data Visualization and Analytics. 
* You can read our research journal [here](https://www.researchgate.net/publication/357794060_Automated_Aquaponics_System_to_Support_Sustainable_Development_Goals) or at ``` research-journal```
* This project also support Sustainable Development Goals (SDG) number 11 - Sustainable Cities and Communities
![](https://github.com/suzarilshah/agriphonics/blob/main/prototype-diagram/SDG.jpg) 

## Methodology

This project relies heavily on Azure Cloud Concept. You might want to look into [these resources](https://docs.microsoft.com/en-us/learn/modules/intro-to-azure-fundamentals/) if you are beginner to Cloud Computing.

### Concept
![](https://github.com/suzarilshah/agriphonics/blob/main/prototype-diagram/physical%20concept.jpg)

We will use 3x ESP8266 / ESP32 for this project. Each of the sensors will be connected to each node and the nodes will transmit different data from each other. The sensors data will be sent to Azure IoT Hub and Azure Stream Job Analytics. After that, these data will be processed in PowerBI and visualized in PowerApps. 

### Physical Diagram
In the end, all of these elements will be integrated in the aquaponics environment as below:
![](https://github.com/suzarilshah/agriphonics/blob/main/prototype-diagram/Figure.PNG)

All of the coding for the IoT nodes is available at ``` codings-iot ```

### Requirements

You can refer to our [previous setup](https://github.com/suzarilshah/smartaquaponics) for the physical aquaponics and Electronics setup. For this project we will add two more sensors;
* Total Dissolve Solids + Electric Conductance sensor - to determnine the level of Ammonia and pollutants
* Water flow sensor - determine the volume of water 
* pH level sensor

## Software Setup - updated!
![](https://github.com/suzarilshah/agriphonics/blob/main/prototype-diagram/block-diagram.jpg)

* Microsoft Azure Cloud Subscriptions
  - Azure IoT Hub - to create IoT nodes, receive sensors data from IoT nodes and send the data to Azure Stream Job Analytics
  - Azure Stream Job Analytics - to create a steady flow of data to PowerBI
  
* Microsoft 365 with PowerPlatform license activated
  - PowerBI - for Data Analytics
  - PowerApps - for Data Visualizations

### Azure Setup

Azure IoT Hub - Below are my notes on how to set the environment for Azure Cloud and the IoT Devices. You can use your own way to set these up. I use VSCode for the IDE since there are a lot of extension that I can use. You can always use Arduino IDE to code your IoT devices if you are comfortable with that.

	1. Configure the Azure IoT Hub -- from Azure Portal
		a. RG
		b. Subscription
		c. Region
		d. Name - for Iot Hub
		e. Pricing - Scaling (Free Tier)
		f. Deploy --> Go to resources
		g. Shared Access Policy --> Connection String (Connect IoT device to Iot Hub)
		h. Connect IoT device and Edge devices
    
	2. Create IoT device
		a. IoT device
			i. Web Interface
				1) Name - device ID
				2) Auth type - Symmetric Key
				3) Copy the Primary Connection String to connect the device to the Hub
			
	3. Install the MX Chip Driver
		a. St.com --> STSW-LINK009 -- https://www.st.com/en/development-tools/stsw-link009.html
    
	4. Install VS Code
		a. Install Extension
			i. Arduino
			ii. Azure IoT Tools
			iii. Azure IoT Hub Toolkit
			iv. Azure IoT device Workbench
      
	5. Configure Arduino device
		a. File > Preference > Settings > Type: Arduino > Look for: .json file
		b. Paste "Arduino Path" -- Arduino IDE Path -- "arduino.path": "C:\\Program Files (x86)\Arduino",
		c. Paste "Arduino additional URL" -- github repo -- 
			i. "arduino.additionalUrls": "https://raw.githubusercontent.com/VSChina/azureiotdevkit_tools/master/package_azureboard_index.json"


	6. Install MXChip on VSCode
		a. Press F1 > Arduino Board Manager
		b. Install MXChip - latest version
		c. Connect ESP 32 device to the PC
		d. Set the COM Port
		e. Set the device - the MXChip Board
		f. If want to see example code press F1: Open Example Code
		

After that, you can code your IoT nodes, one-by-one by referring to ``` codings-iot ``` [repository](https://github.com/suzarilshah/agriphonics/tree/main/codings-iot)

Replace the variable below with your ``` Wi-Fi SSID and Password ``` and ``` Azure Scope ID (your IoT Hub FQDN), Device ID and Connection String ``` 

```
#define WIFI_SSID "<ENTER WIFI SSID HERE>"
#define WIFI_PASSWORD "<ENTER WIFI PASSWORD HERE>"

const char* SCOPE_ID = "<ENTER SCOPE ID HERE>";
const char* DEVICE_ID = "<ENTER DEVICE ID HERE>";
const char* DEVICE_KEY = "<ENTER DEVICE primary/secondary KEY HERE>";
```

After setting up all these requirements, you will need to check your IoT device connection to Azure Cloud. You are expected to see outputs as below on your Azure IoT Hub dashboard:

![image](https://user-images.githubusercontent.com/72111395/156929291-3420f465-2895-495a-bafb-bdac77aa8059.png)

Your serial monitor on COM port should show:
![image](https://user-images.githubusercontent.com/72111395/156929329-914359f1-7ec9-477f-8536-e3c6dd813c58.png)

Congratulations! Your IoT nodes are connected to the Clouds!

## Azure Stream Jobs Analytics + PowerBI dataset

You can refer to my notes here as how to set the Stream Jobs and PowerBI datasets:

		a. Search in the Resource marketplace
			i. Job name
			ii. Subscription
			iii. RG
			iv. Location
			v. Env: Cloud
			vi. Open the resource
		b. Create Input - from our IoT Hub
			i. Add Stream Input > IoT Hub
``` Fill in the description as below: ```

![image](https://user-images.githubusercontent.com/72111395/156929458-5942c0aa-a507-4be1-ac11-6e22774a0041.png)

 c. Create Output - from our IoT Hub to display data to PowerBI
			i. Add Stream Input > IoT Hub > PowerBI > Configure as required
      
You are set to configure your PowerBI! However to proceed to PowerBI, you will need to have a Microsoft 365 Subscription that has PowerPlatform license assigned to you. I believe after you have created PowerBI, you can set your dashboard like below:

![image](https://user-images.githubusercontent.com/72111395/156929617-2544e6aa-4999-4dea-9d44-b1471b263c4c.png)

## Power BI setup Instructions

	• Power BI Desktop. The Windows desktop application 
	• Power BI Service. The online Software as a Service (SaaS) (https://app.powerbi.com/home)
	• Mobile apps. These apps are designed for Android, iOS, and Windows mobile devices
	• Power BI Report Server. After you create your Power BI reports using Desktop, you can publish them to an on-premises report server
	
	I. How to Insert Data (Get Data-Connectors and Get Sample Data)
		○ Home --> Get Data --> more (data source choices) --> choose Excel file (any kind of file to combine)
		○ Navigator will show the file which has the full excel tables separately --> choose table -->click load
		○ Click right panel to see tables in the 'Fields'
		○ Data panel at left to see the line table as excel file
		○ Model or relationship panel at left to see the whole relationship based on file chosen
	II. Query Editor
		○  Navigator --> choose file --> edit
		○ New tab will show (Power Query Editor)
		○ Setting Query (Left panel)
		○ Note: In this section we can clean messy data that does not necessary. (click change type at left panel from data chosen)
	III.  Data Visual
		○ Go to 'Report' panel
		○ expend 'Visualizations' panel (Drag from data at fields panel to show data visually)
			▪ Card element 
			▪ Edit data at the Filters 
			▪ Text box (as label)
			▪ Image
			▪ Chart 
			▪ Graph


## Power Apps

```
Open Power Apps Studio in browser : Power Apps --> Log in Power Apps


How to Create Custom App
	i. Start from data --> Excel Online (OneDrive / gdrive)
		○ Note that Excel file need to have the table
	ii. Choose Excel file (.xlsx) --> Choose table (Tasks) --> Click 'Connect'
		○ Power Apps will generate automatically the excel file to an app
	iii. Click F5 to view apps

Creating Design from 'Tree View'

	I. BrowseScreen (First view when open the apps)
	
		○ Subtitle
		○ Title
		○ App Name
		
	II. DetailScreen --> Advance option to change the properties (need to unlocked) --> edit fx
	
		○ Detail form (open Properties to 'Edit Fields' --> rearrange the data to be shown)
		○ TDS_DataCard
		○ EC_DataCard
		○ TEMP_DataCard
		○ PH_DataCard
		○ Time_DataCard
	• AppName
	• Edit Icon
		
	III. EditScreen
		○ EditForm (DataCard)
	• AppName
	• Edit Icon


Design:
	▪ Choose from Theme (Home --> Theme)
```

## Output from PowerBI
![image](https://user-images.githubusercontent.com/72111395/156929876-482195f7-0476-4835-8fd0-24335322c6c9.png)

## Output from PowerApps
![image](https://user-images.githubusercontent.com/72111395/156929920-7ecf538d-147b-4ba3-95ae-c83d91527ce4.png) ![image](https://user-images.githubusercontent.com/72111395/156929926-70de912e-4cab-4f07-8b3b-8faf72c4f820.png)

With that, you are all set to collect, analyze and visualize your dataset for your Aquaponics Solutions!

## Conclusions

In conclusion, the implementations of these technology really made an impact to me, especially on how capable our technology in contributing to green technology and science! As usual, if you need help or want to ask question, feel free to [email me](mailto:suzarilshah@gmail.com) or reach me on [LinkedIn](https://www.linkedin.com/in/suzarilshah/). 

Thank you!







