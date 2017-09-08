function togglePresident() {
    var image = document.getElementById('president');
    if (image.src.match("natural")) {
        image.src = "pictures/president_percentage.png";
    } else {
        image.src = "pictures/president_natural.png";
    }
}

function toggleVicePresident() {
    var image = document.getElementById('vice_president');
    if (image.src.match("natural")) {
        image.src = "pictures/vice_percentage.png";
    } else {
        image.src = "pictures/vice_natural.png";
    }
}

function toggleTechCore() {
    var image = document.getElementById('tech_core');
    if (image.src.match("natural")) {
        image.src = "pictures/core_percentage.png";
    } else {
        image.src = "pictures/core_natural.png";
    }
}

function toggleLanguage() {
    var image = document.getElementById('favorite_language');
    if (image.src.match("natural")) {
        image.src = "pictures/language_percentage.png";
    } else {
        image.src = "pictures/language_natural.png";
    }
}

function togglePet() {
    var image = document.getElementById('favorite_pet');
    if (image.src.match("natural")) {
        image.src = "pictures/pet_percentage.png";
    } else {
        image.src = "pictures/pet_natural.png";
    }
}
