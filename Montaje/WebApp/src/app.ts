import config from "./controllers/devices/config.js";
import data from "./controllers/devices/data.js";
import signDevices from "./controllers/devices/sign.js";
import userConfig from "./controllers/users/config.js";
import userData from "./controllers/users/data.js";
import devices from "./controllers/users/devices.js";
import signUsers from "./controllers/users/sign.js";
import users from "./controllers/users/users.js";
import errorHandler from "./middlewares/errors.js";
import express from "express";


const app = express();

try {

    app.use(express.json());

    app.get("/ping", (req, res) => {
        res.send("pong");
    });

    app.get("/health", (req, res) => {
        res.send("ok");
    });

    app.use("/api/devices/sign", signDevices);
    app.use("/api/devices/config", config);
    app.use("/api/devices/data", data);

    app.use("/api/users/users", users);
    app.use("/api/users/devices", devices);
    app.use("/api/users/sign", signUsers);
    app.use("/api/users/data", userData);
    app.use("/api/users/config", userConfig);

    app.use(errorHandler);

} catch (error) {

    console.log(error);

}

export default app;
