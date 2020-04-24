# BlindyBands

## Presentation

BlindyBands is an IoT project targetting visually impaired persons, providing them a way to navigate outside by themselves, only with a smartphone a pair of connected bracelets.


## Requirements

### Embedded hardware

### Embedded software

### Paired mobile application

Because we're targetting iOS and Android devices, we used Ionic framework, so a basic Ionic v5 installtion is required. Then, just install registered npm modules and follow instructions on how to build / deploy to a real device on Ionic official documentation.


## Usage

The bracelets must have been paired to the smartphone and fully charged in order to work. In the application, just say the address of your destination, and that's all ! Application will determine coordinates of your destination by giving address vocally, your current location and will determine which route you should take to reack your goal safely. When you'll be ready to go, just push the bracelet button, and the application will start streaming the route via bluetooth connection. Just let you guide by the vibrations of your devices.

- Continuous vibration : Turn right of left (depending on which bracelet is reacting), until the vibration is gone
- Alternate vibrations : Something is ahead (> 50 cm)
- 2 seconds vibration  : Both bracelets are vibrating for a duration of 2s indicates that you reached your destination

Bracelets have an embedded battery, needing to be charged regularly. BlindyBands is provided with an induction battery charger. Just let the bracelets on the charger and it'll be done !


## What remains to do ?

### Embedded system

### Mobile application

Mobile app is, at this time, a bit far away from its final state. A lot of things remains to do, and some implemented features are not working well.

- Current geoposition is not accurate
- Determined route seems to not work. Waypoints are not corrects
- Navigation API is giving Right/Left angles relative to true north. This is not considered at this time.
- Bluetooth connexion is set up, but not tested, as we could not interface it to Tinkercad simulation.

There's also a lot of things to do to truly have a visually-impaired-friendly application, as it today required to tap on a button to start voice recording.