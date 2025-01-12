from flask import Flask, render_template, request, redirect, url_for,render_template_string

app = Flask(__name__)


@app.route('/', methods=['GET', 'POST'])
def index():
    return render_template('homepage.html')

@app.route("/recipe/<recipe_name>")
def recipe(recipe_name):
    recipe_data = {
        "jalebi": {
            "ingredients": [
                "2 cups all-purpose flour",
                "1/2 cup yogurt",
                "1 cup sugar",
                "1/2 cup water",
                "A pinch of saffron",
                "Oil for frying",
            ],
            "instructions": [
                "Prepare the batter by mixing flour, yogurt, and water to form a smooth paste. Let it ferment for 4-5 hours.",
                "Heat oil in a pan for frying.",
                "Fill the batter into a piping bag or squeeze bottle.",
                "Pipe spiral shapes directly into the hot oil and fry until golden.",
                "Prepare sugar syrup with water, sugar, and saffron. Heat until slightly sticky.",
                "Dip the fried jilebis in the warm sugar syrup for a few seconds and serve hot.",
            ],
            "description": "Jilebi is a popular Indian sweet made of deep-fried batter soaked in saffron-flavored sugar syrup. It's a crispy, juicy delight often enjoyed during festivals and celebrations.",
        },
        "macaron": {
            "ingredients": [
                "1 cup almond flour",
                "1 3/4 cups powdered sugar",
                "3 egg whites",
                "1/4 cup granulated sugar",
                "Food coloring (optional)",
                "Buttercream or ganache for filling",
            ],
            "instructions": [
                "Preheat the oven to 300°F (150°C).",
                "Sift almond flour and powdered sugar together.",
                "Whisk egg whites until soft peaks form, then gradually add granulated sugar until stiff peaks form.",
                "Fold the dry ingredients into the egg whites gently.",
                "Add food coloring if desired, and pipe small circles onto parchment paper.",
                "Let the macarons sit for 30 minutes to form a skin, then bake for 15-20 minutes.",
                "Cool completely and sandwich with buttercream or ganache filling.",
            ],
            "description": "Macarons are delicate and sweet French cookies made with almond flour and filled with a variety of delicious creams or ganaches. They're a treat for both the eyes and the taste buds!",
        },
        "doughnut": {
            "ingredients": [
                "3 1/4 cups all-purpose flour",
                "2 tsp yeast",
                "1/2 cup milk",
                "1/4 cup sugar",
                "2 eggs",
                "1/4 cup butter",
                "Oil for frying",
                "Powdered sugar or glaze for topping",
            ],
            "instructions": [
                "Activate the yeast in warm milk with a pinch of sugar.",
                "Mix the activated yeast with flour, sugar, eggs, and butter to form a dough. Let it rise for 1 hour.",
                "Roll out the dough and cut into doughnut shapes.",
                "Heat oil in a pan and fry the doughnuts until golden brown.",
                "Dust with powdered sugar or dip in glaze before serving.",
            ],
            "description": "Doughnuts are soft, fluffy, deep-fried treats that come in a variety of flavors. Perfect for a sweet snack or a breakfast indulgence!",
        },
        "croissant": {
            "ingredients": [
                "4 cups all-purpose flour",
                "1/4 cup sugar",
                "2 tsp salt",
                "2 1/4 tsp yeast",
                "1 1/4 cups milk",
                "2 sticks butter (cold)",
                "1 egg (for egg wash)",
            ],
            "instructions": [
                "Prepare the dough by mixing flour, sugar, salt, yeast, and milk. Let it rest for 30 minutes.",
                "Roll out the dough, place cold butter in the center, and fold it over. Chill for 30 minutes.",
                "Roll out and fold the dough several times to create layers. Chill between each fold.",
                "Cut the dough into triangles, roll them into crescent shapes, and let them rise for 1 hour.",
                "Brush with egg wash and bake at 375°F (190°C) for 20-25 minutes until golden brown.",
            ],
            "description": "Croissants are flaky, buttery pastries with a golden crust. A perfect accompaniment to coffee or tea, they are a staple of French bakeries.",
        },
        "Apple Pie": {
            "ingredients": [
                "2 1/2 cups all-purpose flour",
                "1 cup unsalted butter",
                "6 apples (peeled and sliced)",
                "1/2 cup sugar",
                "2 tsp cinnamon",
                "1 egg (for egg wash)",
            ],
            "instructions": [
                "Prepare the crust by mixing flour and butter. Chill for 30 minutes.",
                "Roll out the dough and line a pie dish with half of it.",
                "Fill with apples mixed with sugar and cinnamon.",
                "Cover with the remaining dough, seal the edges, and cut slits on top.",
                "Brush with egg wash and bake at 375°F (190°C) for 50 minutes.",
            ],
            "description": "Apple Pie is a classic dessert with a flaky crust and a sweet, spiced apple filling. Perfect with a scoop of vanilla ice cream!",
        }
    }
    recipe_name = recipe_name.lower()
    recipe = recipe_data.get(recipe_name, {})
    return render_template(
        "recipe.html",
        recipe_name=recipe_name,
        ingredients=recipe.get("ingredients", []),
        instructions=recipe.get("instructions", []),
        description=recipe.get("description", "No description available."),
    )

blacklist = [
    'config', 
    'self', 
    '__class__', 
    '__mro__', 
    '__init__',  
    '__getitem__', 
    '__globals__', 
    '__builtins__', 
    '__os__', 
    'subprocess', 
    'eval', 
    '__module__',
    '__subclasses__',
    '__name__',
    '<',
]


@app.route('/share', methods=['POST'])
def add_recipe():
    name = request.form.get('name', '')  
    for i in blacklist:
            if i in name:
                print(i,"found")
                return render_template_string("Unacceptable input found !")
    try:
        template = f"""
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Thank You for Joining!</title>
    <script src="https://cdn.tailwindcss.com"></script>
</head>
<body class="bg-blue-100 flex items-center justify-center min-h-screen">
    <div class="text-center p-8 bg-white rounded-lg shadow-lg max-w-md w-full">
        <h1 class="text-4xl font-semibold text-blue-600">Thank You, {name}!</h1>
        <p class="mt-4 text-lg text-gray-700">We appreciate you sharing your recipe with us! Stay tuned for more delicious updates.</p>
        <a href="/" class="mt-6 inline-block bg-pink-500 text-white text-lg px-8 py-4 rounded-lg shadow-md hover:bg-pink-600 transition">
            Go Back
        </a>
    </div>
</body>
</html>


"""

        return render_template_string(template)
    except:
        return render_template_string("An error occurred while adding the recipe.")


if __name__ == '__main__':
    app.run(host="0.0.0.0", port=9000, debug=True)
