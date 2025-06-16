import app from "./src/app.js";
import { connectToDatabase } from "./src/utils/connection.js";


await connectToDatabase();
app.listen(3000, () => { console.log("Server is running on port 3000"); });
