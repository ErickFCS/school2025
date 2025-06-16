import models from "../../models/Index.js";
import { dataSchema } from "../../types/data.js";
import { Router } from "express";
import { z } from "zod";


const data = Router();

data.post("/", async (req, res, next) => {
    try {
        const newData = z.array(dataSchema).parse(req.body);
        await models.SensedData.bulkCreate(newData);
        res.status(201).send();
    } catch (error) {
        next(error);
    }
});

export default data;
