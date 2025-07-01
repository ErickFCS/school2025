import { NextFunction, Request, Response } from "express";


const errorHandler = (err: Error, req: Request, res: Response, next: NextFunction) => {
    switch (err.name) {
        case "ValidationError":
            res.status(400).json({
                error: err.message,
                message: "Bad Request",
                status: "error"
            });
            break;
        case "NotFoundError":
            res.status(404).json({
                error: err.message,
                message: "Not Found",
                status: " error"
            });
            break;
        case "UnauthorizedError":
            res.status(401).json({
                error: err.message,
                message: "Unauthorized",
                status: "error"
            });
            break;
        default:
            console.error(err.stack);
            res.status(500).json({
                error: err.message,
                message: "Internal Server Error",
                status: "error"
            });
            break;
    }
    next();
};

export default errorHandler;
