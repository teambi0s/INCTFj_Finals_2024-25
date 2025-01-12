import express from 'express';
import crypto from 'crypto';
import { v4 as uuidv4 } from 'uuid';
import puppeteer from 'puppeteer';
import session from 'express-session'; 
import { visit } from './bot.js';

const app = express();

app.use(express.json()); 
app.use(express.urlencoded({ extended: true })); 
const secret = crypto.randomBytes(32).toString('hex');
app.use(session({
    secret: secret, 
    resave: false,
    saveUninitialized: true,
    cookie: { secure: false }
}));

const notes = [];

app.use((req, res, next) => {
    res.set({
        "Content-Security-Policy": "default-src 'self';style-src 'unsafe-inline'; script-src 'self'",
    })
    next();
});

app.get('/', (req, res) => {
    const nonce = crypto.randomBytes(16).toString('hex');

    if (!req.session.userId) {
        req.session.userId = uuidv4();
    }

    const userNotes = notes.filter(note => note.userId === req.session.userId );
    
    const notesHtml = userNotes
        .map(
            (note, index) =>
                `<li><b>Note ${index + 1}:</b> <a href="/note/${note.id}">View</a></li>`
        )
        .join('');

    res.send(`
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <title>Simple Note App</title>
        <style>
            body {
                font-family: Arial, sans-serif;
                margin: 0;
                padding: 0;
                background-color: #f4f4f9;
            }
            header {
                background-color: #4CAF50;
                color: white;
                padding: 10px 0;
                text-align: center;
            }
            main {
                margin: 20px;
                padding: 20px;
                background: white;
                border-radius: 8px;
                box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
            }
            textarea {
                width: 100%;
                margin-bottom: 10px;
                padding: 10px;
                font-size: 16px;
                border: 1px solid #ddd;
                border-radius: 4px;
            }
            button {
                background-color: #4CAF50;
                color: white;
                border: none;
                padding: 10px 20px;
                cursor: pointer;
                font-size: 16px;
                border-radius: 4px;
            }
            button:hover {
                background-color: #45a049;
            }
            ul {
                list-style-type: none;
                padding: 0;
            }
            ul li {
                margin: 5px 0;
            }
            a {
                color: #4CAF50;
                text-decoration: none;
            }
            a:hover {
                text-decoration: underline;
            }
        </style>
    </head>
    <body>
        <header>
            <h1>Note-Taking App</h1>
        </header>
        <main>
            <h2>Add a Note</h2>
            <form method="POST" action="/add">
                <textarea name="note" id="note" rows="4" cols="50" placeholder="Write your note here..." required></textarea><br>
                <button type="submit" id="createNote">Add Note</button>
            </form>
            <h2>Your Notes</h2>
            <ul>
                ${notesHtml}
            </ul>
        </main>
    </body>
    </html>
    `);
});

// Add note route
app.post('/add', (req, res) => {
    const { note } = req.body;
    if (!note || note.trim() === '') {
        return res.status(400).send('Note content cannot be empty.');
    }

    if (!req.session.userId) {
        return res.status(401).send('You must be logged in to add notes.');
    }

    const safeNote = note.replace('<', '').replace('>', '').replace('"', '').replace("'", '').replace('`', '');

    const id = uuidv4();
    notes.push({ id, content: safeNote, userId: req.session.userId });
    res.redirect('/');
});

app.get('/note/:id', (req, res) => {
    const nonce = crypto.randomBytes(16).toString('hex');

    const note = notes.find((n) => n.id === req.params.id);

    if (!note) {
        return res.status(404).send('Note not found');
    }

    res.send(`
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <title>View Note</title>
        <style>
            body {
                font-family: Arial, sans-serif;
                margin: 0;
                padding: 20px;
                background-color: #f4f4f9;
            }
            main {
                background: white;
                border-radius: 8px;
                padding: 20px;
                box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
                max-width: 600px;
                margin: 20px auto;
            }
            a {
                color: #4CAF50;
                text-decoration: none;
            }
            a:hover {
                text-decoration: underline;
            }
        </style>
    </head>
    <body>
        <main>
            <h1>Note Details</h1>
            <p><b>ID:</b> ${note.id}</p>
            <p><b>Content:</b> ${note.content}</p>
            <a href="/">Back to Home</a>
        </main>
    </body>
    </html>
    `);
});

app.get('/report', async (req, res) => {
    const queryUrl = req.query.url;

    if (!queryUrl) {
        return res.status(400).send('Bad Request: No URL provided in "url" parameter');
    }

    try {
        await visit(queryUrl); 
        res.send('URL has been visited successfully.');
    } catch (err) {
        console.error(err);
        res.status(500).send('Internal Server Error');
    }
});

app.get('*',(req,res)=>{
    res.set('Content-Type','text/plain');
    res.status = 404;
    res.send(`Error: ${req.originalUrl} was not found`);
});

// Start the server
const listener = app.listen(process.env.PORT || 3000, () => {
    console.log(`Your app is listening on port ${listener.address().port}`);
});
